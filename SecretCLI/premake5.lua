-- premake5.lua
workspace "Secret"
  configurations { "Debug", "Release" }
  location "../build"

project "SecretLIB"
  kind "SharedLib"
  language "C++"
  location "build/SecretLIB"
  targetdir "build/lib"

  files { "common/**" }

project "SecretCLIParser"
  kind "ConsoleApp"
  language "C++"
  location "build/SecretCLIParser"
  targetdir "build/SecretCLIParser/bin"

  files { "CLIParser/**" }
  
  libdirs { "build/lib/**" }
  links { "SecretLIB" }
  

project "SecretCLI"
  kind "ConsoleApp"
  language "C++"
  location "build/SecretCLI"
  targetdir "./"

  libdirs { "build/lib/**" }
  links { "SecretLIB" }

  files { "CLI/**","CLI/**" }



