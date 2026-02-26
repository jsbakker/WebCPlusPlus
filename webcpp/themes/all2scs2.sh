#!/bin/sh

for SCHEMES in `ls *.scs`; do
	scs2scs2.pl $SCHEMES
done
