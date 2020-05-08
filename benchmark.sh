#!/usr/bin/env bash

## CPU and Memory usage logging
cpumemmon() (
    # "Experimental - I have no idea what I'm doing"
    $* &>/dev/null &
    pid="$!"
    trap ':' INT
    echo 'CPU  MEM'
    while sleep 1; do ps --no-headers -o '%cpu,%mem' -p "$pid"; done
    kill "$pid"
)


## Build Project
build(){
    # Remove previous build directory if it exists and recreate it
    rm -rf build
    mkdir -p build
    cd build
    cmake ..
    make
    cd ..
}


echo "Time for building:"
time build > /dev/null


## Set CAD Directory
export G4HORUS_CAD_DIR=$(pwd)/cad


## Create output dir and run full simulation
mkdir -p out
cd out
TS=$(date +%Y-%m-%dT%H-%M-%S)
mkdir "${TS}"
cd "${TS}"


echo "Time for startup:"
time ../../build/G4Horus -m ../../scripts/test.mac > /dev/null


echo "Time for long simulation:"
time nice -n 19 ../../build/G4Horus -t 30 -k hist -m ../../scripts/bench.mac > /dev/null
