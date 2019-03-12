#!/bin/sh

#source /data/jmayer/software/root-6.00.02/bin/thisroot.sh

if [ -n "$1" ]
then
    DIR=$1
else
    DIR=$(ls -d out/*/ | tail -n 1)
fi

root -l -b -q 'efficiency.cxx("'${DIR}'")'
