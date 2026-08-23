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

  filter "system:windows"
    systemversion "latest"
    defines { "PLATFORM_WINDOWS" }
    includedirs {
      "../../engine/vendored/SDL/src/build/include",
      "../../engine/vendored/SDL/src_mixer/include",
      "../../engine/vendored/SDL/src_ttf/include",
      "../../engine/vendored/SDL/src_image/include",
      "../../engine/vendored/glm",
      "../../engine/vendored/SDL/src/include"
    }
		libdirs { 
      "../../engine/vendored/SDL/src/build/Debug",
      "../../engine/vendored/SDL/src_mixer/build/Debug",
      "../../engine/vendored/SDL/src_ttf/build/Debug",
      "../../engine/vendored/SDL/src_image/build/Debug",
			"../../engine/vendored/non-git/glew/build/cmake/build/lib/Debug",
      "../../build/secret/lib", 
			}
		links { "SDL3", "SDL3_ttf", "SDL3_image", "SDL3_mixer", "user32", "glew32d", "opengl32", "secret" }

  links { "secret" }

  files { "src/**" }



