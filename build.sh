#!/bin/bash

./scripts/Move-build.sh
cmake -B./build/ -S./
cd ./build
make
./RoboCore
