-- premake5.lua
workspace "ELOgine"
  configurations { "Debug", "Release" }
  location "../build" 

project "ELOgine"
  kind "SharedLib"
  language "C++"

  libdirs { "../engine/vendored/SDL/src/build", "../engine/vendored/SDL/src_image/build", "../engine/vendored/SDL/src_ttf/build" }
  links { "SDL3", "SDL3_ttf", "SDL3_image" }

  location "../build/ELOgine" 
  targetdir "../build/ELOgine/lib"

  files { "../engine/src/**.hpp", "../engine/src/**.cpp" }
