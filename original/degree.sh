#!/bin/sh

gcc one.c -lm -o one.out
for n in  100 160;
do
./one.out $n
done
rm one.out
