#!/bin/bash
cd ..
echo "starting premake script..."
premake5 gmake
wait
cd build/SecretCLI/
echo "starting make script..."
make
wait
cd ../SecretCLIParser/ 
echo "starting make script..."
make
wait
cd ../SecretLIB/ 
echo "starting make script..."
make
wait
