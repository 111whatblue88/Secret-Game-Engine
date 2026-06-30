## Info

As there is no GUI, the SecretCLI is the main way to manage building/running things in the engine.
This document lists all currently available commands.

## Command List 

### Project Commands 

list -- lists all projects in the /projects folder
build -- builds the given project
  flags: --release, --debug
run -- runs the given project
  flags: --suppress (suppresses project output)
create -- creates a new project, with the name given
remove -- removes the given project
info -- prints info from the projectInfo file

### Engine Commands 

build -- builds the engines source files, use "all" after to build vendored source files as well
  flags: --release, --debug
info -- prints info from the engine/engineInfo file

### Context Commands

project -- changes the CLI to assume you are referring to a project
clear -- clears all context


