#!/bin/sh
source /data/jmayer/Geant4/geant4.10.00.p02-install/bin/geant4.sh
source /data/jmayer/Geant4/geant4.10.00.p02-install/share/Geant4-10.0.2/geant4make/geant4make.sh
rm -rf build
mkdir build
cd build
cmake -DGeant4_DIR=/data/jmayer/Geant4/geant4.10.00.p02-install/lib64/Geant4-10.0.2 ..
make
./G4Horus -t 10
