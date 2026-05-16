-- premake5.lua
workspace "HUGE"
  configurations { "Debug", "Release" }
  location "../build" 

project "HUGE"

  kind "SharedLib"
  language "C++"

  location "../build/HUGE" 
  targetdir "../build/HUGE/lib"

  libdirs { "../engine/vendored/SDL/src/build", "../engine/vendored/SDL/src_image/build", "../engine/vendored/SDL/src_ttf/build" }
  links { "SDL3", "SDL3_ttf", "SDL3_image" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    files { "../engine/debug/**.hpp", "../engine/debug/**.cpp" }

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    files { "../engine/src/**.hpp", "../engine/src/**.cpp" }

