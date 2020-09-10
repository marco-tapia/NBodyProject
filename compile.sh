#! /bin/bash

#compile the serial version

gcc -o nbody_serial serialBF.c -lm

#compile the parallel version 

gcc -o nbody_openmp -fopenmp openmpBF.c -lm
