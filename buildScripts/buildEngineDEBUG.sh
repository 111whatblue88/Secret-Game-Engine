#!/bin/bash
premake5 gmake
wait
cd ..
cd build
make config=debug 
wait
