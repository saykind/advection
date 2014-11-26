#!/usr/bin/gnuplot -persist
set terminal postscript enhanced eps color
set output 'plot.eps'

set grid
set xrange [0:21]
set xtics 2
set xlabel 'number of processes'
set ylabel 'execution time, sec'

plot 'data.dat' u 3:1 w points ps .8 notitle ,'data.dat' u 3:1 notitle smooth csplines

