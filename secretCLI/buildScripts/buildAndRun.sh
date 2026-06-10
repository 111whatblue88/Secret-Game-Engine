#!/bin/bash
echo "starting premake script..."
premake5 gmake
wait
cd ../build
echo "starting make script..."
make
wait
./bin/*
