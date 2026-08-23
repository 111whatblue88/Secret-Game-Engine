@echo off
cd ..
echo starting premake script...
START /wait premake5 vs2022
echo building visual studio solution...
cd build
START /wait MSBuild.exe ./Secret.sln
cd ..
echo copying executable to main directory...
COPY build\SecretCLI\bin\Debug\SecretCLI.exe .\