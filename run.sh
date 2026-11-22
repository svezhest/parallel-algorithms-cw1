#!/usr/bin/env bash
set -e

cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build -j

PARLAY_NUM_THREADS=4 ./build/bench
