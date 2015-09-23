#!/bin/bash
#This is the submission script for submitting the job into ACENET grid engine.
#Remember here you don't need to specify the -np parameter. Open MPI will 
#obtain this information directly from Grid Engine.

#Grid Engine options.
#$ -cwd
#$ -l h_rt=01:00:00
#$ -pe ompi* 4

#Compile the application.
ls > ligandlist ./Ligand
mkdir -p Output
mkdir -p ProcessedLigand
make

#Run the application.
echo "MPI-Vina is running..."
mpirun mpiVINA > Output/MpiVina.log
echo "Processing has finished"
echo "See the MpiVina.log file."

#Result analysis.
echo "Analysizing the results..."
cd Output
grep "  1 " *.txt | cut -c1-12,35-42 > result 
#grep "  1 " *.txt | cut -c1-7,30-35 > result
echo "See the 'result' file in 'Output' directory."
#cat result

echo "Sorting the results..."
sort -n +1 -2 result -o SortedResult
echo "See the 'SortedResult' file in 'Output' directory."
#cat SortedResult
