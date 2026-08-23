#!/bin/bash
cd ..
echo "starting premake script..."
premake5 gmake
wait
echo "starting make script..."
cd build
make
wait
