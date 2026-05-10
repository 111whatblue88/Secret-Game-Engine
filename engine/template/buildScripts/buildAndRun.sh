#!/bin/bash
echo "starting premake script..."
premake5 gmake
wait
cd ../build
echo "starting make script..."
make
wait
echo "copying shared libraries..."
mkdir lib
cp ../../../build/ELOgine/lib/* ./lib
cp ../../../engine/vendored/SDL/src/build/* ./lib
cp ../../../engine/vendored/SDL/src_ttf/build/* ./lib
cp ../../../engine/vendored/SDL/src_image/build/* ./lib
./bin/*
