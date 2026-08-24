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
    files { "common/**.cpp", "CLIParser/**.cpp" }
    removefiles { "common/**LNX.cpp", "CLIParser/**LNX.cpp" }

  filter "system:linux"
    defines { "PLATFORM_LINUX" }
    links { "pthread" }
    files { "common/**.cpp", "CLIParser/**.cpp" }
    removefiles { "common/**WIN.cpp", "CLIParser/**WIN.cpp" }


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
    files { "common/**.cpp", "CLI/**.cpp" }
    removefiles { "common/**LNX.cpp", "CLI/**LNX.cpp" }

  filter "system:linux"
    defines { "PLATFORM_LINUX" }
    links { "pthread" }
    files { "common/**.cpp", "CLI/**.cpp" }
    removefiles { "common/**WIN.cpp", "CLI/**WIN.cpp" }


