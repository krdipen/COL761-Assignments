#!/bin/sh

if [ $1 = "-apriori" ]; then
	InpF=$2
	Xval=$3
	OutF=$4
	./apriori $InpF $Xval $OutF
elif [ $2 = "-plot" ]; then
	InpF=$1
	python plot.py $InpF
elif [ $1 = "-prefixspan"]; then
	InpF=$2
	Xval=$3
	OutF=$4
	./prefixspan $InpF $Xval $OutF
