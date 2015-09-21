# File      : makefile
# Author    : Md Mokarrom Hossain
# Username  : x2013idf
# Course    : CSCI 522
# Purpose   : makefile in order to ease the compilation procedure.

mpiVINA: mpiVINAv2.o CLinkedList.o
	mpicc -o mpiVINA mpiVINAv2.o CLinkedList.o -lmpi
	
mpiVINAv2.o: mpiVINAv2.c CLinkedList.h
	mpicc -c mpiVINAv2.c
	
CLinkedList.o: CLinkedList.c CLinkedList.h
	mpicc -c CLinkedList.c 
	
clean:
	rm -rf *o mpiVINA