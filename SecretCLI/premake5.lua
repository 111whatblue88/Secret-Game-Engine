-- premake5.lua
workspace "Secret"
  configurations { "Debug", "Release" }
  location "build"

project "SecretCLIParser"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  architecture "x86_64"
  location "build/SecretCLIParser"

  targetdir "build/SecretCLIParser/bin/%{cfg.buildcfg}"
  objdir "build/SecretCLIParser/obj/%{cfg.buildcfg}"

  filter "system:windows"
    systemversion "latest"
    defines { "PLATFORM_WINDOWS" }
    links { "user32" }
    files { "win64/CLIParser/**", "win64/common/**" }

  filter "system:linux"
    defines { "PLATFORM_LINUX" }
    links { "pthread" }
    files { "linux/CLIParser/**", "linux/common/**" }

project "SecretCLI"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  architecture "x86_64"
  location "build/SecretCLI"

  dependson {
    "SecretCLIParser"
  }

  targetdir "build/SecretCLI/bin/%{cfg.buildcfg}"
  objdir "build/SecretCLI/obj/%{cfg.buildcfg}"

  filter "system:windows"
    systemversion "latest"
    defines { "PLATFORM_WINDOWS" }
    links { "user32" }
    files { "win64/CLI/**", "win64/common/**" }

  filter "system:linux"
    defines { "PLATFORM_LINUX" }
    links { "pthread" }
    files { "linux/CLI/**", "linux/common/**" }