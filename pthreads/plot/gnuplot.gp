#!/usr/bin/gnuplot -persist
set terminal postscript enhanced eps color

set grid
set xtics 1
set ytics 1
set xlabel 'number of processes'
set ylabel 'acceleration'

set fit quiet
set fit errorvariables
fit [1:3] k*(x-1)+1 'data.dat' u 1:(42.25/$2) via k
set label 1 sprintf("k = %.4f", k) at 2.5, 1.5

set output 'PTHREADS_plot_16.eps'
set title 'PTHREADS: 16 core machine'
set xrange [0:16]
plot 'data.dat' u 1:(42.25/$2) w points ps .8 notitle, 'data.dat' u 1:(42.25/$2) notitle smooth csplines

