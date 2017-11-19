#!/bin/sh

## Geant 4 Version
# If a specific Geant4 version should be used, adapt and uncomment these lines.
# source /opt/geant4/4.10.00.p02/bin/geant4.sh
# source /opt/geant4/4.10.00.p02/share/Geant4-10.0.2/geant4make/geant4make.sh
echo "Using Geant4 Version `geant4-config --version` in `dirname $(dirname $(geant4-config --prefix))`"


## Build Project
# Remove previous build directory if it exists and recreate it
rm -rf build
mkdir -p build
cd build
cmake ..
make -j 10
cd ..


## Set CAD Directory
export G4HORUS_CAD_DIR=`pwd`/cad


## Create output dir and run full simulation
mkdir -p out
cd out
TS=$(date +%Y-%m-%dT%H-%M-%S)
mkdir ${TS}
cd ${TS}


## Macro File
if [ -n "$1" ]
then
    MACRO=../../$1
else
    MACRO=../../scripts/test.mac
fi


# Run executable in batch mode, niced and multithreaded
nice -n 19 ../../build/G4Horus -t 30 -k hist -m ${MACRO}
