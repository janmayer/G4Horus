#!/bin/sh

set -e

## 3D performance
# On some systems, using the following option can improve
# the 3D performance of the detector visualization.
# On others, it will crash the Geant4 window.
export LIBGL_ALWAYS_INDIRECT=y

## Geant 4 Version
# If a specific Geant4 version should be used, adapt and uncomment these lines.
# source /data/jmayer/software/geant4.10.05/bin/geant4.sh
echo "Using Geant4 Version $(geant4-config --version) in $(dirname $(dirname $(geant4-config --prefix)))"

## Build Project
# Remove previous build directory if it exists and recreate it
#rm -rf build
mkdir -p build
cd build

cmake ..
make

# Run executable
./G4Horus
