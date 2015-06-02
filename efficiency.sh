#!/bin/sh

source /data/jmayer/software/root-6.00.02/bin/thisroot.sh
root -l -b -q 'efficiency.cxx("'$(ls -d out/*/ | tail -n 1)'")'
