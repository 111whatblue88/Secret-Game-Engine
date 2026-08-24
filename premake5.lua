-- premake5.lua
workspace "secret"
  configurations { "Debug", "Release" }
  location "build" 

include "engine/vendored/Secret-Output-Helper"

project "secret"

  kind "StaticLib"
  language "C++"
  cppdialect "C++20"
  architecture "x86_64"

  location "build/secret" 
  targetdir "build/secret/lib"

  dependson "Secret-Output-Helper"

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
      "engine/vendored/glew/build/cmake/build/lib/Debug",
    }
    links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "opengl32", "glew32d", "Secret-Output-Helper" }

    files { "engine/src/**.hpp", "engine/src/**.cpp" }
    removefiles { "engine/src/**LNX.cpp" }

    filter "configurations:Debug"
      defines { "DEBUG" }

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

  filter { "system:linux" }
    libdirs { 
      "engine/vendored/SDL/src/build", 
      "engine/vendored/SDL/src_image/build",
      "engine/vendored/SDL/src_ttf/build",
      "engine/vendored/SDL/src_mixer/build",
      "engine/vendored/glew/build/lib",
      "engine/vendoredSecret-Output-Helper/build/lib"
    }
    links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "GL", "GLU", "GLEW", "Secret-Output-Helper" }

    files { "engine/src/**.hpp", "engine/src/**.cpp" }
    removefiles { "engine/src/**WIN.cpp" }

  filter "configurations:debug"
    defines "DEBUG"
    runtime "Debug"
    symbols "On"

  filter "configurations:release"
    defines "NDEBUG"
    runtime "Release"
    symbols "Off"

