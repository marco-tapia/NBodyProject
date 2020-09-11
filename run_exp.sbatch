#!/bin/bash
#
# This sbatch script runs the program a couple of times

# Job settings
#SBATCH --nodes=1
#SBATCH --time=0:20:00
#SBATCH --output=nbody_runs.out
echo "Serial runs"

echo "------------------------"
./nbody_serial

echo "------------------------"

echo "Parallel runs"
#./nbody_openmp
echo "------------------------"
