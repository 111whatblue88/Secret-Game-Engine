-- premake5.lua
workspace "TemplateProject"
  configurations { "Debug", "Release" }
  location "../build"

project "TemplateProject"
  kind "WindowedApp"
  language "C++"
  location "../build/TemplateProject"
  targetdir "../build/bin"

  linkoptions {
      "-Wl,-rpath,'$$ORIGIN/../lib'"
  }
  libdirs { 
    "../../../build/HUGE/lib", 
    "../../../engine/vendored/SDL/src/build/",
    "../../../engine/vendored/SDL/src_ttf/build/",
    "../../../engine/vendored/SDL/src_image/build/",
  } 
  links { "HUGE", "SDL3", "SDL3_ttf", "SDL3_image" }

  files { "../src/**.cpp" }

