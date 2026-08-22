#include "../../../engine/vendored/argparse/include/argparse/argparse.hpp"

#include <algorithm>
#include <complex>
#include <cstdio>
#include <iostream>
#include <memory>
#include <nlohmann/json_fwd.hpp>
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
#include <nlohmann/json.hpp>
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

      filesystem::execCommand("premake5 gmake");
      fs::current_path(fs::current_path()/"build");
      if (engineBuild["--release"] == true) {
        filesystem::execCommand("make config=release");
      } else {
        filesystem::execCommand("make config=debug");
      }

      return 0;
    }
    

    filesystem::execCommand("git submodule init");
    filesystem::execCommand("git submodule update");

    fs::current_path(fs::current_path()/"engine/vendored/SDL/src");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ..");
    filesystem::execCommand("make");

    locateToEngineRoot();

    fs::current_path(fs::current_path()/"engine/vendored/SDL/src_ttf");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ..");
    filesystem::execCommand("make");

    locateToEngineRoot();

    fs::current_path(fs::current_path()/"engine/vendored/SDL/src_image");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ..");
    filesystem::execCommand("make");

    locateToEngineRoot();

    fs::current_path(fs::current_path()/"engine/vendored/SDL/src_mixer");
    filesystem::execCommand("mkdir build");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ..");
    filesystem::execCommand("make");

    locateToEngineRoot();

    fs::current_path(fs::current_path()/"engine/vendored/glew");
    filesystem::execCommand("make extensions");
    filesystem::execCommand("make");
    filesystem::execCommand("sudo make install");
    filesystem::execCommand("make clean");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("cmake ./cmake");
    filesystem::execCommand("make -j4");

    locateToEngineRoot();

    if (engineBuild["--clean"] == true) {
      if (fs::exists(fs::current_path()/"build")) {
        fs::remove_all(fs::current_path()/"build");
      }
    }

    filesystem::execCommand("premake5 gmake");
    fs::current_path(fs::current_path()/"build");
    filesystem::execCommand("make");

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








