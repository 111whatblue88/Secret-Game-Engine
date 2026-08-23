-- premake5.lua
workspace "{{NAME}}"
  configurations { "Debug", "Release" }
  location "build"

project "{{NAME}}"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  architecture "x86_64"
  location "build/test"
  targetdir "build/bin"

  includedirs {
    "../../engine/vendored/SDL/src//include",
    "../../engine/vendored/SDL/src_mixer/include",
    "../../engine/vendored/SDL/src_ttf/include",
    "../../engine/vendored/SDL/src_image/include",
    "../../engine/vendored/glm",
  }

  filter "system:windows"
    systemversion "latest"
    defines { "PLATFORM_WINDOWS" }
		libdirs { 
      "../../engine/vendored/SDL/src/build/Debug",
      "../../engine/vendored/SDL/src_mixer/build/Debug",
      "../../engine/vendored/SDL/src_ttf/build/Debug",
      "../../engine/vendored/SDL/src_image/build/Debug",
			"../../engine/vendored/glew/build/cmake/build/lib/Debug",
      "../../build/secret/lib", 
			}
		links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "user32", "glew32d", "opengl32", "secret" }

    files { "src/**.cpp" }
    removefiles { "src/**LNX.cpp" }

  filter "system:linux"
    systemversion "latest"
    defines { "PLATFORM_LINUX" }
    libdirs { 
      "../../engine/vendored/SDL/src/build", 
      "../../engine/vendored/SDL/src_image/build",
      "../../engine/vendored/SDL/src_ttf/build",
      "../../engine/vendored/SDL/src_mixer/build",
      "../../engine/vendored/glew/build/lib",
      "../../build/secret/lib", 
    }
		links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "GLEW", "GL", "secret:static" }
    linkoptions { "-Wl,-rpath=./" }

    files { "src/**.cpp" }
    removefiles { "src/**WIN.cpp" }


