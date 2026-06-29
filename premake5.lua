-- premake5.lua
workspace "secret"
  configurations { "Debug", "Release" }
  location "build" 

project "secret"

  kind "SharedLib"
  language "C++"

  location "build/secret" 
  targetdir "build/secret/lib"

  libdirs { "engine/vendored/SDL/src/build", "engine/vendored/SDL/src_image/build", "engine/vendored/SDL/src_ttf/build", "engine/vendored/SDL/src_mixer/build" }
  links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    files { "engine/src/**.hpp", "engine/src/**.cpp" }

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    files { "engine/src/**.hpp", "engine/src/**.cpp" }

