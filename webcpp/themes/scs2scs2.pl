#!/usr/bin/perl -w

my $scs = shift or die "Usage: $0 <scsfile>\n";
(my $sc2 = $scs) =~ s/\.scs\z/.Scs2/;

open(SCSFILE, "<$scs") or die "$!: cannot read $scs";
open(SC2FILE, ">$sc2") or die "$!: cannot write to $sc2";

my @scheme = <SCSFILE>;
chomp @scheme;
chop @scheme;

foreach $element (@scheme) {
	$element =~ s/^#//;
}

close(SCSFILE);

select(SC2FILE);

print<<"EOF";
<?xml version="1.0"?>
<!DOCTYPE SyntaxColourScheme2 SYSTEM "WebcppScheme2.dtd">
<SyntaxColourScheme2>
  <bgcolor>$scheme[0]</bgcolor>
  <preproc>$scheme[1]</preproc>
  <nortext>$scheme[2]</nortext>
  <symbols>$scheme[2]</symbols>
  <keyword>$scheme[3]</keyword>
  <keytype>$scheme[3]</keytype>
  <integer>$scheme[4]</integer>
  <floatpt>$scheme[4]</floatpt>
  <dblquot>$scheme[5]</dblquot>
  <sinquot>$scheme[5]</sinquot>
  <comment>$scheme[6]</comment>
</SyntaxColourScheme2>
EOF

close(SC2FILE);
select(STDOUT);
print("Webcpp scheme $scs was upgraded to $sc2 in Scs2 format!\n");
