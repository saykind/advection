#!/usr/bin/gnuplot -persist
set terminal postscript enhanced eps color

set grid
set xtics 1
set ytics 1
set xlabel 'number of processes'
set ylabel 'acceleration'

set fit quiet
set fit errorvariables
fit [0:15] k*x 'data16.dat' u 1:(17.27/$2) via k
set label 1 sprintf("k = %.4f", k) at 4, 2.5

set output 'MPI_plot_16.eps'
set title 'MPI: 16 core machine'
set xrange [0:18]
plot [0:18] 'data16.dat' u 1:(17.27/$2) w points ps .8 notitle, 'data16.dat' u 1:(17.27/$2) notitle smooth csplines

