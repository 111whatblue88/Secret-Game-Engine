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
if ! [ -d "build" ]; then
  echo "No build files found. Build the project with \"project build $1\""
  exit
fi
cd build
if ! [ -d "bin" ]; then
  echo "No binary files found. Build the project with \"project build $1\""
  exit
fi
stdbuf -oL ./bin/*
