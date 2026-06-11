-- premake5.lua
workspace "Secret"
  configurations { "Debug", "Release" }
  location "build"

project "SecretCLIParser"
  kind "ConsoleApp"
  language "C++"
  location "build/SecretCLIParser"
  targetdir "build/SecretCLIParser/bin"

  files { "CLIParser/**", "common/**" }
  

project "SecretCLI"
  kind "ConsoleApp"
  language "C++"
  location "build/SecretCLI"
  targetdir "./"

  files { "CLI/**", "common/**" }



