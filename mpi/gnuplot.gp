#!/usr/bin/gnuplot -persist
set terminal postscript enhanced eps color

set grid
set xtics 2
set xlabel 'number of processes'
set ylabel 'execution time, sec'

set output 'plot.eps'
set title 's32303 machine'
set xrange [0:21]
plot 'data.dat' u 3:1 w points ps .8 notitle ,'data.dat' u 3:1 notitle smooth csplines

set output 'plot16.eps'
set title '16 core machine'
set yrange [0:20]
set xrange [0:18]
plot [0:18] 'data16.dat' u 1:2 w points ps .8 notitle, 'data16.dat' u 1:2 notitle smooth csplines

