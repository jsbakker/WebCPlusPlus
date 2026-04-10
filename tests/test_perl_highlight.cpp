// test_perl_highlight.cpp
// Ported from PerlHighlightTests.swift

#include <gtest/gtest.h>
#include "highlight_test_helper.h"

struct PerlHighlightTest : ::testing::Test {
    std::string hl(const std::string& src) { return highlight(src, "pl"); }
};

TEST_F(PerlHighlightTest, KeywordsAreHighlighted) {
    EXPECT_NE(hl("and").find("<font CLASS=keyword>and</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, TypesAreHighlighted) {
    EXPECT_NE(hl("binmode").find("<font CLASS=keytype>binmode</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, IntegersAreHighlighted) {
    EXPECT_NE(hl("42").find("<font CLASS=integer>42</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, FloatsAreHighlighted) {
    EXPECT_NE(hl("3.14").find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, DoubleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl(R"("hello")").find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PerlHighlightTest, SingleQuotedStringsAreHighlighted) {
    EXPECT_NE(hl("'hello'").find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PerlHighlightTest, BacktickStringsAreHighlighted) {
    EXPECT_NE(hl("`ls -la`").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PerlHighlightTest, ApostropheInsideDoubleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"("it's fine")");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PerlHighlightTest, DoubleQuoteInsideSingleQuoteIsNotSeparatelyHighlighted) {
    auto html = hl(R"('say "hi"')");
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PerlHighlightTest, SingleQuoteInsideBacktickIsNotSeparatelyHighlighted) {
    auto html = hl("`it's fine`");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_EQ(html.find("<font CLASS=sinquot>"), std::string::npos);
}

TEST_F(PerlHighlightTest, SymbolsAreHighlighted) {
    EXPECT_NE(hl("x + y").find("<font CLASS=symbols>+</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, ScalarVariablesAreHighlighted) {
    EXPECT_NE(hl("$variable").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PerlHighlightTest, ArrayVariablesAreHighlighted) {
    EXPECT_NE(hl("@array").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PerlHighlightTest, HashVariablesAreHighlighted) {
    EXPECT_NE(hl("%hash").find("<font CLASS=preproc>"), std::string::npos);
}

TEST_F(PerlHighlightTest, DuplicateSigilsDoNotHang) {
    auto html = hl("%for% $die$ @keys@ bless");
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keyword>bless</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, HeredocStringIsHighlighted) {
    auto html = hl("my $text = <<HEREDOC;\nhello world\nHEREDOC");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PerlHighlightTest, HeredocQuotedMarkerIsHighlighted) {
    auto html = hl("my $t = <<'EOF';\nraw text\nEOF");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PerlHighlightTest, HeredocInsideStringIsNotTriggered) {
    auto html = hl(R"(my $s = "use <<EOF for heredocs";)");
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
}

TEST_F(PerlHighlightTest, InlineCommentsAreHighlighted) {
    EXPECT_NE(hl("# comment").find("<font CLASS=comment># comment</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, LabelsAreHighlighted) {
    EXPECT_NE(hl("label:").find("<font CLASS=preproc>label:</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, UnderscoreIntegersAreHighlighted) {
    EXPECT_NE(hl("1_000_000").find("<font CLASS=integer>1_000_000</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, UnderscoreFloatsAreHighlighted) {
    EXPECT_NE(hl("1.123_456").find("<font CLASS=floatpt>1.123_456</font>"), std::string::npos);
}

TEST_F(PerlHighlightTest, ComprehensiveSnippetHighlightsAllRules) {
    auto html = hl(R"(# Perl comment
use strict;
my $scalar = 42;
my @array = (3.14, "hello");
my %hash = ('key' => 'value');
binmode STDOUT;
sub example {
    bless {}, 'Example';
    $scalar = $scalar + 1;
label:
    print $scalar;
})");
    EXPECT_NE(html.find("<font CLASS=keyword>bless</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=keytype>binmode</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=integer>42</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=floatpt>3.14</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=dblquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=sinquot>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=symbols>+</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=comment># Perl comment</font>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>"), std::string::npos);
    EXPECT_NE(html.find("<font CLASS=preproc>label:</font>"), std::string::npos);
}
