-- premake5.lua
workspace "secret"
  configurations { "Debug", "Release" }
  location "../build"

project "secretCLI"
  kind "ConsoleApp"
  language "C++"
  location "../build/secretCLI"
  targetdir "../build/bin"

  files { "../src/**.hpp","../src/**.cpp" }

  includedirs
  {
    "../src",
    "../src/parser",
    "../src/printingTools"
  }
