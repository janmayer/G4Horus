#!/bin/sh

## Geant 4 Version
# If a specific Geant4 version should be used, adapt and uncomment these lines.
# source /opt/geant4/4.10.00.p02/bin/geant4.sh
# source /opt/geant4/4.10.00.p02/share/Geant4-10.0.2/geant4make/geant4make.sh
echo "Using Geant4 Version `geant4-config --version` in `dirname $(dirname $(geant4-config --prefix))`"

## Build Project
# Remove previous build directory if it exists and recreate it
#rm -rf build
mkdir -p build
cd build

cmake -DWITH_NTUPLE=OFF -DWITH_GEANT4_UIVIS=ON -DWITH_MT=OFF ..
make

# Run executable
./G4Horus
