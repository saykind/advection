#!/usr/bin/gnuplot -persist
set terminal postscript enhanced eps color

set grid
set xtics 1
set ytics 1
set xlabel 'number of processes'
set ylabel 'acceleration'

set fit quiet
set fit errorvariables
fit [0:14] k*x 'data16.dat' u 1:(43.2/$2) via k
set label 1 sprintf("k = %.4f", k) at 4, 2.5

set output 'PTHREADS_plot_16.eps'
set title 'PTHREADS: 16 core machine'
set xrange [0:19]
plot 'data16.dat' u 1:(43.2/$2) w points ps .8 notitle, 'data16.dat' u 1:(43.2/$2) notitle smooth csplines

