@echo off
cd ..
echo starting premake script...
START /wait premake5 vs2022
echo building VS solution..
cd build
START /wait MSBuild.exe Secret.sln
echo copying CLI executable...
COPY SecretCLI\bin\Debug\SecretCLI.exe ..\
echo done
