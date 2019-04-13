#!/bin/zsh

INPUT_FILE='input.txt'
OUTPUT_FILE='output.txt'
NUM_OF_RUNS=8

C_SRC=c_src.c
CPP_SRC=cpp_src.cpp

###################
##  change this  ##
###################

num_elements=(0.1 1 10 20 30 40 50 60 70 80 90 100)
factor=9000
repeat_max=900000

OUTPUT_TXT_FILE='unordered_map_fetch.txt'

###################
###################

meassure()
{
	echo "num of elements = $2" >> $OUTPUT_FILE
	echo "num of repetitions = $3" >> $OUTPUT_FILE
	echo $2 > $INPUT_FILE
	echo $3 >> $INPUT_FILE
	hyperfine -i -r $NUM_OF_RUNS ./$1 | grep "Time" >> $OUTPUT_FILE
}

echo '' > $OUTPUT_FILE
echo 'c' >> $OUTPUT_FILE
echo '' >> $OUTPUT_FILE

for i in ${num_elements[@]}; do
	meassure c_prog $((i * factor)) $((repeat_max/(i*factor)))
done

echo '' >> $OUTPUT_FILE
echo 'cpp' >> $OUTPUT_FILE
echo '' >> $OUTPUT_FILE

for i in ${num_elements[@]}; do
	meassure cpp_prog $((i * factor)) $((repeat_max/(i*factor)))
done

cp $OUTPUT_FILE $OUTPUT_TXT_FILE
