# File      : runMpiVINA.bash
# Author    : Md Mokarrom Hossain
# Username  : x2013idf
# Course    : CSCI 522
# Purpose   : bash script in order to ease the execution.

#!/bin/bash
ls > ligandlist ./Ligand
mkdir -p Output
mkdir -p ProcessedLigand
make
mpirun -np 5 mpiVINA
#result analysis
cd Output
grep "  1 " *.txt | cut -c1-12,35-42 >result
#grep "  1 " *.txt | cut -c1-7,30-35 >result
echo "Check 'result' file in Output directory for merger result."
#cat result
sort -n +1 -2 result -o SortedResult
echo "Check 'SortedResult' file in Output directory for sorted result."
#cat SortedResult