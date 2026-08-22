-- premake5.lua
workspace "Secret"
  configurations { "Debug", "Release" }
  platforms { "Windows", "Linux" }

  location "build"

project "SecretCLIParser"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  architecture "x86_64"

  location "build/SecretCLIParser"
  targetdir "build/SecretCLIParser/bin"

  filter { "platforms:Windows" }
    system "windows"
    toolset "msc"
    files { "CLIParser/**", "common/**" }
    removefiles { "CLIParser/**LNX.cpp", "common/**LNX.cpp" }

  filter { "platforms:Linux" }
    system "linux"
    toolset "clang"
    files { "CLIParser/**", "common/**" }
    removefiles { "CLIParser/**WIN.cpp", "common/**WIN.cpp" }
  

project "SecretCLI"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  architecture "x86_64"

  location "build/SecretCLI"
  targetdir "./"

  filter { "platforms:Windows" }
    system "windows"
    files { "CLIParser/**", "common/**" }
    removefiles { "CLI/**WIN.cpp", "common/**WIN.cpp" }

  filter { "platforms:Linux" }
    system "linux"
    files { "CLI/**", "common/**" }
    removefiles { "CLI/**WIN.cpp", "common/**WIN.cpp" }



