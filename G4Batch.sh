#!/bin/sh

source /opt/geant4/4.10.00.p02/bin/geant4.sh
source /opt/geant4/4.10.00.p02/share/Geant4-10.0.2/geant4make/geant4make.sh

#export CC=/usr/local/bin/clang
#export CXX=/usr/local/bin/clang++

rm -rf build
mkdir build
cd build
cmake -DGeant4_DIR=/opt/geant4/4.10.00.p02/lib64 ..
make -j 4

nice -n 19 ./G4Horus -t 30 -m doit.mac
