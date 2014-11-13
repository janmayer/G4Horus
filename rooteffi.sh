#!/bin/sh

#export CC=/usr/local/bin/clang
#export CXX=/usr/local/bin/clang++

source /data/jmayer/software/root-6.00.02/bin/thisroot.sh
#source /data/jmayer/software/root-latest/bin/thisroot.sh
root -l -b -q 'effi.cxx("/scratch/jmayer/G4/")'
