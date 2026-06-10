#!/bin/bash
echo "starting premake script..."
premake5 gmake
wait
cd ../build/secretCLI/
echo "starting make script..."
make
wait
cd ../parser/ 
echo "starting make script..."
make
wait
cd ../bin
./secretCLI
