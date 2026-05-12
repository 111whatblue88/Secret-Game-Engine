#!/bin/bash
echo "starting premake script..."
premake5 gmake
wait
cd ../build
echo "starting make script..."
make
wait
echo "copying shared libraries..."
mkdir -p lib
cp ../../../build/HUGE/lib/* ./lib > /dev/null 2>&1
cp ../../../engine/vendored/SDL/src/build/* ./lib > /dev/null 2>&1
cp ../../../engine/vendored/SDL/src_ttf/build/* ./lib > /dev/null 2>&1
cp ../../../engine/vendored/SDL/src_image/build/* ./lib > /dev/null 2>&1
./bin/*
