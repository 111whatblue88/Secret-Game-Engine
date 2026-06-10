-- premake5.lua
workspace "secret"
  configurations { "Debug", "Release" }
  location "../build/bin"

project "secret"
  kind "ConsoleApp"
  language "C++"
  location "../build/parser"
  targetdir "../build/parser/bin"

  files { "../parser/**" }

  includedirs
  {
    "../../engine/vendored/argparse/include/**",
  }

project "secretCLI"
  kind "ConsoleApp"
  language "C++"
  location "../build/secretCLI"
  targetdir "../build/bin"

  files { "../CLI/**.hpp","../CLI/**.cpp" }

  includedirs
  {
    "../CLI",
    "../CLI/printingTools"
  }
