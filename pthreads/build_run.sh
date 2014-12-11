#!/bin/bash

gcc -Wall -g -fopenmp linear.c -lm -o a.out -lpthread
for n in {1..18};
do
	./a.out $n >> data.dat
done
rm a.out
