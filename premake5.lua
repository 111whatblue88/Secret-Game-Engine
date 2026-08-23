-- premake5.lua
workspace "secret"
  configurations { "Debug", "Release" }
  location "build" 

include "engine/vendored/Secret-Output-Helper"

project "secret"

  kind "SharedLib"
  language "C++"
  cppdialect "C++20"
  architecture "x86_64"

  location "build/secret" 
  targetdir "build/secret/lib"

  includedirs {
    "engine/vendored/glm"
  }

  libdirs { "engine/vendored/SDL/src/build", 
    "engine/vendored/SDL/src_image/build",
    "engine/vendored/SDL/src_ttf/build",
    "engine/vendored/SDL/src_mixer/build",
    "engine/vendored/non-git/glew/build/lib",
  }

  filter { "system:windows" }
    links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "opengl32","glew", "Secret-Output-Helper" }

  filter { "system:linux" }
    links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "GL", "GLU", "GLEW", "Secret-Output-Helper" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    files { "engine/src/**.hpp", "engine/src/**.cpp" }

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    files { "engine/src/**.hpp", "engine/src/**.cpp" }

