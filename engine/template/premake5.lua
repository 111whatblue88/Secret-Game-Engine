-- premake5.lua
workspace "Template"
  configurations { "Debug", "Release" }
  location "build"

project "TemplateProject"
  kind "WindowedApp"
  language "C++"
  location "build/TemplateProject"
  targetdir "build/bin"

  local rpaths = {
    "$$ORIGIN/../../../../build/secret/lib",
    "$$ORIGIN/../../../../engine/vendored/SDL/src/build",
    "$$ORIGIN/../../../../engine/vendored/SDL/src_ttf/build",
    "$$ORIGIN/../../../../engine/vendored/SDL/src_image/build"
  }

  linkoptions {
    "-Wl,-rpath,'" .. table.concat(rpaths, ":") .. "'"
  } 

  libdirs { 
    "../../build/secret/lib", 
    "../../engine/vendored/SDL/src/build/",
    "../../engine/vendored/SDL/src_ttf/build/",
    "../../engine/vendored/SDL/src_image/build/",
  } 
  links { "SDL3", "SDL3_ttf", "SDL3_image", "secret" }

  files { "src/**" }

