### HUGE 
## Huge Unused Game-Engine

Huge is a small game engine I'm developing, it very bad and very broken

## Building
# MacOS/Windows
will never be possible
# Linux
1. Clone the repo
2. Run the (in order) scripts /buildScripts/buildDependencies.sh, /buildScripts/buildEngine.sh 

## Usage
To create a project run the .createNewProject.sh file in the root repo directory
Rename the project in /projects to whatever you want 

Project source files need to be placed in /src, it searches that directory recursively 
To build a project go in the /PROJECTFOLDER/buildScripts and run either build.sh or buildAndRun.sh 

## Documentation
I have not made documentation for this project yet, you are on your own. 

# extra info
You might be thinking "why is there so many .sh files?". Well eventually everything that is 
currently managed by shell files will be managed by the hugeCLI, which will be a small CLI program which
manages small automation engine tasks, like project management and compilation.

You might also be thinking "wow, this readme sucks", that means its working.
