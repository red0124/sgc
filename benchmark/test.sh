#!/bin/zsh

INPUT_FILE='input.txt'
OUTPUT_FILE='output.txt'
NUM_OF_RUNS=8

C_SRC=c_src.c
CPP_SRC=cpp_src.cpp

###################
##  change this  ##
###################

POW_BASE=1.2
POW_MIN=55
POW_MAX=65

OUTPUT_DOCUMENT='map_fetch'

###################
###################

meassure()
{
	echo "num of elements = $2" >> $OUTPUT_FILE
	echo $2 > $INPUT_FILE
	hyperfine -i -r $NUM_OF_RUNS ./$1 | grep "Time" >> $OUTPUT_FILE
}

power()
{
	let num_of_elements=$2
	let power=$2
	let base=$1
	let num_of_elements=$(($base**$power))
}

echo '' > $OUTPUT_FILE
echo 'c' >> $OUTPUT_FILE
echo '' >> $OUTPUT_FILE

for (( i = $POW_MIN; i < $POW_MAX; i++ )); do
	power POW_BASE i
	meassure c_prog $num_of_elements
done

echo '' >> $OUTPUT_FILE
echo 'cpp' >> $OUTPUT_FILE
echo '' >> $OUTPUT_FILE

for (( i = $POW_MIN; i < $POW_MAX; i++ )); do
	power POW_BASE i
	meassure cpp_prog $num_of_elements
done

mkdir -p $OUTPUT_DOCUMENT
cp $OUTPUT_FILE $OUTPUT_DOCUMENT
cp $C_SRC $OUTPUT_DOCUMENT
cp $CPP_SRC $OUTPUT_DOCUMENT
