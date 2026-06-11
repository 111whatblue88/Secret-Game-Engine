#include "../../engine/vendored/argparse/include/argparse/argparse.hpp"

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

#include "../common/common.hpp"

using namespace secret;
using namespace output;
using namespace filesystem;

using json = nlohmann::json;

int main(int argc, char *argv[]) {

  locateToEngineRoot(); 

  std::ifstream f("SecretCLI/cliInfo.json");
  json cliInfo = json::parse(f);

  argparse::ArgumentParser program("SecretCLI", cliInfo["ver"]);

  // Project Parsing
  argparse::ArgumentParser projectParser("project");

  argparse::ArgumentParser projectBuild("build");
  projectBuild.add_argument("projectName");
  argparse::ArgumentParser projectRun("run");
  projectRun.add_argument("projectName");
  argparse::ArgumentParser projectInfo("info");
  projectInfo.add_argument("projectName");

  projectParser.add_subparser(projectBuild);
  projectParser.add_subparser(projectRun);
  projectParser.add_subparser(projectInfo);

  // Engine Parsing
  argparse::ArgumentParser engineParser("engine");
  argparse::ArgumentParser engineBuild("build");
  argparse::ArgumentParser engineBuildAll("all");
  engineBuild.add_subparser(engineBuildAll);
  argparse::ArgumentParser engineInfo("info");

  engineParser.add_subparser(engineInfo);
  engineParser.add_subparser(engineBuild);

  // Add all parsers to main parser 
  program.add_subparser(projectParser);
  program.add_subparser(engineParser);

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  if (program.is_subcommand_used("project")) {
    if (projectParser.is_subcommand_used("build")) {
      locateToEngineRoot();
      std::string projectName = projectBuild.get<std::string>("projectName");

      if (!fs::exists(fs::current_path()/"projects")) {
        printColor("No projects.. Use \"project create {NAME}\" to create a project\n", color::red);
        return 1;
      }
      fs::current_path(fs::current_path()/"projects");
      if (!fs::exists(fs::current_path()/projectName)) {
        printColor("Given project does not exist\n", color::red);
        return 1;
      }
      fs::current_path(fs::current_path()/projectName);
      filesystem::execCommand("premake5 gmake");
      fs::current_path(fs::current_path()/"build");
      filesystem::execCommand("make");
    } 
    if (projectParser.is_subcommand_used("run")) {
      locateToEngineRoot();
      std::string projectName = projectRun.get<std::string>("projectName");

      if (!fs::exists(fs::current_path()/"projects")) {
        printColor("No projects.. Use \"project create {NAME}\" to create a project\n", color::red);
        return 1;
      }
      fs::current_path(fs::current_path()/"projects");
      if (!fs::exists(fs::current_path()/projectName)) {
        printColor("Given project does not exist\n", color::red);
        return 1;
      }
      fs::current_path(fs::current_path()/projectName);
      if (!fs::exists(fs::current_path()/"build"/"bin")) {
        printColor("Project exists, but required build directories/files do not exist\n", color::red);
        return 1;
      }
      fs::current_path(fs::current_path()/"build"/"bin");
      filesystem::execCommand(std::format("./{}", projectName).c_str());
    } 
    if (projectParser.is_subcommand_used("info")) {
      locateToEngineRoot();
      std::string projectName = projectInfo.get<std::string>("projectName");

      if (!fs::exists(fs::current_path()/"projects")) {
        printColor("No projects.. Use \"project create {NAME}\" to create a project\n", color::red);
        return 1;
      }
      fs::current_path(fs::current_path()/"projects");
      if (!fs::exists(fs::current_path()/projectName)) {
        printColor("Given project does not exist\n", color::red);
        return 1;
      }
      fs::current_path(fs::current_path()/projectName);
      std::ifstream f("projectInfo.json");
      json projectInfo = json::parse(f);
      std::string name = projectInfo["releaseName"];
      std::string desc = projectInfo["description"];
      std::string ver = projectInfo["ver"];
      printColor(std::format("Name: {}\n" ,name), color::white);
      printColor(std::format("Description: {}\n" ,desc), color::white);
      printColor(std::format("Version: {}\n" ,ver), color::white);
    } 
  } 

  if (program.is_subcommand_used("engine")) {
    if (engineParser.is_subcommand_used("build")) {
      locateToEngineRoot();
      if (!engineBuild.is_subcommand_used("all")) {
       

        filesystem::execCommand("premake5 gmake");
        fs::current_path(fs::current_path()/"build");
      filesystem::execCommand("make");

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

      filesystem::execCommand("premake5 gmake");
      fs::current_path(fs::current_path()/"build");
      filesystem::execCommand("make");

    } 
    if (engineParser.is_subcommand_used("info")) {
      locateToEngineRoot();
      std::ifstream f("engine/engineInfo.json");
      json engineInfo = json::parse(f);
      std::string name = engineInfo["releaseName"];
      std::string desc = engineInfo["description"];
      std::string ver = engineInfo["ver"];
      printColor(std::format("Name: {}\n" ,name), color::white);
      printColor(std::format("Description: {}\n" ,desc), color::white);
      printColor(std::format("Version: {}\n" ,ver), color::white);
    } 
  }

}


