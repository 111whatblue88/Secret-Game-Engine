# Secret Game Engine
## Shh!

Secret is a small game engine. Currently with very basic systems (ecs, audio, rendering).
Right now its main rendering API is SDL3, but openGL might be added soon

## Building
### MacOS/Windows
....never
### Linux
1. Clone the repo with "git clone https://github.com/111whatblue88/Secret-Game-Engine.git --recursive"
2. Run the CLI setup script in /SecretCLI/buildScripts
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

