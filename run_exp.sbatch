#!/bin/bash
#
# This sbatch script runs the program a couple of times

# Job settings
#SBATCH --nodes=1
#SBATCH --time=0:20:00
#SBATCH --output=lab1_runs.out

./nbody_serial
