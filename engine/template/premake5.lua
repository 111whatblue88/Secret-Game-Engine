-- premake5.lua
workspace "{{NAME}}"
  configurations { "Debug", "Release" }
  location "build"

project "{{NAME}}"
  kind "WindowedApp"
  language "C++"
  location "build/{{NAME}}"
  targetdir "build/bin"

  local rpaths = {
    "$$ORIGIN/../../../../build/secret/lib",
    "$$ORIGIN/../../../../engine/vendored/SDL/src/build",
    "$$ORIGIN/../../../../engine/vendored/SDL/src_ttf/build",
    "$$ORIGIN/../../../../engine/vendored/SDL/src_image/build",
    "$$ORIGIN/../../../../engine/vendored/SDL/src_mixer/build"
  }

  linkoptions {
    "-Wl,-rpath,'" .. table.concat(rpaths, ":") .. "'"
  } 

  libdirs { 
    "../../build/secret/lib", 
    "../../engine/vendored/SDL/src/build/",
    "../../engine/vendored/SDL/src_ttf/build/",
    "../../engine/vendored/SDL/src_image/build/",
    "../../engine/vendored/SDL/src_mixer/build/",
  } 
  links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer","secret" }

  files { "src/**" }

