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
    "engine/vendored/SDL/src/include", 
    "engine/vendored/SDL/src_image/include",
    "engine/vendored/SDL/src_ttf/include",
    "engine/vendored/SDL/src_mixer/include",
    "engine/vendored/glm"
  }

  filter { "system:windows" }
    libdirs { 
      "engine/vendored/SDL/src/build/Debug", 
      "engine/vendored/SDL/src_image/build/Debug",
      "engine/vendored/SDL/src_ttf/build/Debug",
      "engine/vendored/SDL/src_mixer/build/Debug",
      "engine/vendored/non-git/glew/build/cmake/build/bin/Debug",
    }
    links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "opengl32","glew", "Secret-Output-Helper" }

  filter { "system:linux" }
    libdirs { 
      "engine/vendored/SDL/src/build", 
      "engine/vendored/SDL/src_image/build",
      "engine/vendored/SDL/src_ttf/build",
      "engine/vendored/SDL/src_mixer/build",
      "engine/vendored/non-git/glew/build/lib",
    }
    links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "GL", "GLU", "GLEW", "Secret-Output-Helper" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    files { "engine/src/**.hpp", "engine/src/**.cpp" }

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    files { "engine/src/**.hpp", "engine/src/**.cpp" }

