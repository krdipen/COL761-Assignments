#!/bin/sh

if [ $1 = "-apriori" ]; then
	InpF=$2
	Xval=$3
	OutF=$4
	./apriori $InpF $Xval $OutF
elif [ $1 = "-plot" ]; then
	echo "plot's loop"
elif [ $1 = "-prefixspan"]; then
	echo "prefix"