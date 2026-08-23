#include "../../../../engine/vendored/argparse/include/argparse/argparse.hpp"

#include <algorithm>
#include <complex>
#include <cstdio>
#include <iostream>
#include <memory>
#include "../../../../engine/vendored/json/single_include/nlohmann/json.hpp"
#include <stdexcept>
#include <string>
#include <array>
#include <format>
#include <cstdint>
#include <functional>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <iostream>
#include <filesystem>

#include "engineParser.hpp"
#include "../../common/common.hpp"

using namespace secret;
using namespace parser;
using namespace output;
using namespace filesystem;


EngineParser::EngineParser():
  engineParser("engine", fetchEngineInfo()["ver"]),
  engineBuild("build", " "),
  engineBuildAll("all", " "),
  engineInfo("info", " ")
{
  engineParser.add_description("for managing the engine");
  engineBuild.add_description("builds the engines source files");
  engineBuildAll.add_description("builds the engines source files and the vendored source files");
  engineInfo.add_description("prints info about the engine");

  engineBuild.add_argument("--release")
  .default_value(false)
  .implicit_value(true);

  engineBuild.add_argument("--clean")
  .default_value(false)
  .implicit_value(true);

  engineBuild.add_argument("--debug")
  .default_value(false)
  .implicit_value(true);

  engineBuild.add_subparser(engineBuildAll);
  engineParser.add_subparser(engineInfo);
  engineParser.add_subparser(engineBuild);

}

bool EngineParser::parseArguments() {


  if (engineParser.is_subcommand_used("build")) {
    locateToEngineRoot();
    if (!engineBuild.is_subcommand_used("all")) {

      if (engineBuild["--clean"] == true) {
        if (fs::exists(fs::current_path()/"build")) {
          fs::remove_all(fs::current_path()/"build");
        }
      }

      filesystem::execCommand("premake5 vs2022");
      fs::current_path(fs::current_path()/"build");
      if (engineBuild["--release"] == true) {
        filesystem::execCommand("MSBuild.exe Secret.sln");
      } else {
        filesystem::execCommand("MSBuild.exe Secret.sln");
      }

      return 0;
    }
    

    filesystem::execCommand("git submodule init");
    filesystem::execCommand("git submodule update");

    fs::current_path(fs::current_path()/"engine/vendored/SDL/src");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ..");
    filesystem::execCommand("MSBuild.exe ALL_BUILD.vcxproj");

    // install SDL3 to system as other SDL subsystem installations require it
    printColor("installing SDL3 to system, this will not work if SecretCLI was not run as administrator", color::white);
    filesystem::execCommand("timout 3");
    filesystem::execCommand("MSBuild.exe INSTALL.vcxproj");

    locateToEngineRoot();

    fs::current_path(fs::current_path()/"engine/vendored/SDL/src_ttf");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ..");
    filesystem::execCommand("MSBuild.exe ALL_BUILD.vcxproj");

    locateToEngineRoot();

    fs::current_path(fs::current_path()/"engine/vendored/SDL/src_image");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ..");
    filesystem::execCommand("MSBuild.exe ALL_BUILD.vcxproj");

    locateToEngineRoot();

    fs::current_path(fs::current_path()/"engine/vendored/SDL/src_mixer");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake -DSDLMIXER_VENDORED=OFF ..");
    filesystem::execCommand("MSBuild.exe ALL_BUILD.vcxproj");

    locateToEngineRoot();

    fs::current_path(fs::current_path()/"engine/vendored");

    filesystem::execCommand("curl -L -o glew.zip https://github.com/nigels-com/glew/releases/download/glew-2.3.1/glew-2.3.1.zip");
    filesystem::execCommand("tar -xf glew.zip");
    filesystem::execCommand("del glew.zip");
    filesystem::execCommand("ren glew-2.3.1 glew");

    fs::current_path(fs::current_path()/"glew");

    fs::current_path(fs::current_path()/"build"/"cmake");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ..");
    filesystem::execCommand("MSBuild.exe ALL_BUILD.vcxproj");

    locateToEngineRoot();

    if (engineBuild["--clean"] == true) {
      if (fs::exists(fs::current_path()/"build")) {
        fs::remove_all(fs::current_path()/"build");
      }
    }

    filesystem::execCommand("premake5 vs2022");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("MSBuild.exe Secret.sln");

  } 
  if (engineParser.is_subcommand_used("info")) {
    locateToEngineRoot();
    std::ifstream f("engine/engineInfo.json");
    nlohmann::json engineInfo = nlohmann::json::parse(f);
    std::string name = engineInfo["releaseName"];
    std::string desc = engineInfo["description"];
    std::string ver = engineInfo["ver"];
    printColor(std::format("Name: {}\n" ,name), color::white);
    printColor(std::format("Description: {}\n" ,desc), color::white);
    printColor(std::format("Version: {}\n" ,ver), color::white);
  } 

  return true;
}








