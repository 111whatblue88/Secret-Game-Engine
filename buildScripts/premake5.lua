-- premake5.lua
workspace "HUGE"
  configurations { "Debug", "Release" }
  location "../build" 

project "HUGE"
  kind "SharedLib"
  language "C++"

  libdirs { "../engine/vendored/SDL/src/build", "../engine/vendored/SDL/src_image/build", "../engine/vendored/SDL/src_ttf/build" }
  links { "SDL3", "SDL3_ttf", "SDL3_image" }

  location "../build/HUGE" 
  targetdir "../build/HUGE/lib"

  files { "../engine/src/**.hpp", "../engine/src/**.cpp" }
