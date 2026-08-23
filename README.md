# Secret Game Engine
## Shh!

Secret is a small game engine. Currently with very basic systems (ecs, audio, rendering).
Right now its main rendering API is SDL3, but openGL support is being developed 

## Building
### Windows 

##### Dependencies
Strawberry perl installed\
CMake installed and in path\
An ASM assembler installed and in path\
Premake5 installed and in path\
MSBuild in path\

1. Clone the repo with "git clone https://github.com/111whatblue88/Secret-Game-Engine.git --recursive"
2. Run the buildWindows.bat setup script in /SecretCLI/buildScripts
3. In the CLI, run "engine build all" while running SecretCLI as administrator\
(it needs to be run as administrator because INSTALL.vcxproj in SDL requires it)
### Linux
1. Clone the repo with "git clone https://github.com/111whatblue88/Secret-Game-Engine.git --recursive"
2. Run the buildLinux.sh setup script in /SecretCLI/buildScripts
3. In the CLI, run "engine build all"

## Usage
For a very basic usage, use the SecretCLI and "project create {NAME}", and then "project build {NAME}", "Project run {NAME}".
You can edit the projects source code in {ROOT}/projects/{NAME}/src. The build system searches /src recursively.

## Documentation
I have not made documentation for this project yet, sorry :p

## CLI 
As of recent i have added a CLI tool called "SecretCLI", as there is no GUI you use this to make 
building and running projects easier. Command list is available in SecretCLI/docs, you can also use -h 
in the CLI to get a description for a command

