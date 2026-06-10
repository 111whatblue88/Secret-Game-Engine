#!/bin/bash 

cd ../../..
if ! [ -d "projects" ]; then
  echo "There are no projects. You can create a project with \"project create {NAME}\""
  exit
fi
cd projects
if ! [ -d $1 ]; then
  echo "Project $1 not found"
  exit
fi
cd $1
cd buildScripts
./build.sh
