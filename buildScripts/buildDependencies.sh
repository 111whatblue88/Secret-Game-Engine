#!/bin/bash
echo "initializing submodules"
cd ..
git submodule init
wait
git submodule update
wait

echo "building SDL3"
cd engine/vendored/SDL/src
mkdir -p build
cd build
cmake ..
wait
make 
wait

cd .. 

echo "building SDL3_TTF"
cd engine/vendored/SDL/src_ttf
mkdir -p build
cd build
cmake ..
wait
make 
wait

cd .. 

echo "building SDL3_IMAGE"
cd engine/vendored/SDL/src_image
mkdir -p build
cd build
cmake ..
wait
make 
wait

