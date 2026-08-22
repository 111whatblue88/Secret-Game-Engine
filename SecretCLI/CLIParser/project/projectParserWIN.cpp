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

#include "projectParser.hpp"
#include "../../common/common.hpp"

using namespace secret;
using namespace parser;
using namespace output;
using namespace filesystem;

ProjectParser::ProjectParser():
  projectParser("project", " "),
  projectRun("run", " "),
  projectInfo("info", " "),
  projectCreate("create", " "),
  projectRemove("remove", " "),
  projectList("list", " "),
  projectBuild("build", " ")
{

  projectParser.add_description("for managing user projects");
  projectRun.add_description("runs the given project");
  projectInfo.add_description("gives info about the given project");
  projectCreate.add_description("creates a new project with a given name");
  projectRemove.add_description("removes the given project");
  projectList.add_description("lists the projects available");
  projectBuild.add_description("builds the given project");

  projectBuild.add_argument("projectName");

  projectBuild.add_argument("--release")
  .default_value(false)
  .implicit_value(true);

  projectBuild.add_argument("--debug")
  .default_value(false)
  .implicit_value(true);

  projectBuild.add_argument("--clean")
  .default_value(false)
  .implicit_value(true);

  projectRun.add_argument("projectName");

  projectRun.add_argument("--suppress")
  .default_value(false)
  .implicit_value(true);

  projectInfo.add_argument("projectName");

  projectCreate.add_argument("projectName");

  projectRemove.add_argument("projectName");

  projectParser.add_subparser(projectRemove);
  projectParser.add_subparser(projectList);
  projectParser.add_subparser(projectCreate);
  projectParser.add_subparser(projectBuild);
  projectParser.add_subparser(projectRun);
  projectParser.add_subparser(projectInfo);

}

bool ProjectParser::parseArguments() {

  if (projectParser.is_subcommand_used("list")) {

    locateToEngineRoot();

    if (!fs::exists(fs::current_path()/"projects")) {
      printColor("No projects.. Use \"project create {NAME}\" to create a project\n", color::red);
      return 1;
    }

    fs::current_path(fs::current_path()/"projects");
    filesystem::execCommand("ls");

  }
  if (projectParser.is_subcommand_used("create")) {
    locateToEngineRoot();

    std::string projectName = projectCreate.get<std::string>("projectName");

    if (!fs::exists(fs::current_path()/"projects")) {
      fs::create_directory(fs::current_path()/"projects");
      printColor("projects folder does not exist, creating directory...\n", color::white);
    }
    if (fs::exists(fs::current_path()/"projects"/projectName)) {
      printColor("Project with the same name already exists\n", color::red);

      return 1;
    }

    printColor("created template directory, renaming to project name...\n", color::white);
    fs::create_directory(fs::current_path()/"projects"/"template");
    fs::rename(fs::current_path()/"projects"/"template", fs::current_path()/"projects"/projectName);
    
    printColor("copying template files...\n", color::white);
    fs::copy(
      fs::current_path()/"engine/template",
      fs::current_path()/"projects"/projectName,
      fs::copy_options::recursive
    );

    fs::current_path(fs::current_path()/"projects");
    fs::current_path(fs::current_path()/projectName);

    printColor("replacing instances of template name with project name...\n", color::white);

    std::string replaceString = "{{NAME}}";

    std::ifstream premakeFileStream("premake5.lua");
    std::string premakeFile(
      (std::istreambuf_iterator<char>(premakeFileStream)),
      std::istreambuf_iterator<char>()
    );

    size_t pos = 0;
    while ((pos = premakeFile.find(replaceString, pos)) != std::string::npos)
    {
      premakeFile.replace(pos, replaceString.length(), projectName);
      pos += projectName.length();
    }

    std::ofstream outFile("premake5.lua");
    outFile << premakeFile;

    std::ifstream sourceFileStream("src/main.cpp");
    std::string sourceFile(
      (std::istreambuf_iterator<char>(sourceFileStream)),
      std::istreambuf_iterator<char>()
    );

    pos = 0;
    while ((pos = sourceFile.find(replaceString, pos)) != std::string::npos)
    {
      sourceFile.replace(pos, replaceString.length(), projectName);
      pos += projectName.length();
    }

    std::ofstream outFile2("src/main.cpp");
    outFile2 << sourceFile;

    std::ifstream infoFileStream("projectInfo.json");
    std::string infoFile(
      (std::istreambuf_iterator<char>(infoFileStream)),
      std::istreambuf_iterator<char>()
    );

    pos = 0;
    while ((pos = infoFile.find(replaceString, pos)) != std::string::npos)
    {
      infoFile.replace(pos, replaceString.length(), projectName);
      pos += projectName.length();
    }

    std::ofstream infoFileWrite("projectInfo.json");
    infoFileWrite << infoFile;

    printColor("Successfully created project\n", color::green);

  }
  if (projectParser.is_subcommand_used("remove")) {
    locateToEngineRoot();

    std::string projectName = projectRemove.get<std::string>("projectName");

    if (!fs::exists(fs::current_path()/"projects")) {
      printColor("No projects.. Use \"project create {NAME}\" to create a project\n", color::red);
      return 1;
    }
    fs::current_path(fs::current_path()/"projects");
    if (!fs::exists(fs::current_path()/projectName)) {
      printColor("Given project does not exist\n", color::red);
      return 1;
    }

    fs::remove_all(fs::current_path()/projectName);

    printColor("Project files deleted successfully\n", color::green);

  }
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

    printColor("Building project...\n", color::green);

    fs::current_path(fs::current_path()/projectName);

    
    if (projectBuild["clean"] == true) {
      if (fs::exists(fs::current_path()/"build")) {
        fs::remove_all(fs::current_path()/"build");
      }
    }

    filesystem::execCommand("premake5 gmake");
    fs::current_path(fs::current_path()/"build");
    if (projectBuild["--release"] == true) {
      filesystem::execCommand("make config=release");
    } else {
    filesystem::execCommand("make config=debug");
    }

    printColor("Project built\n", color::green);

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
    if (projectRun["--suppress"] == true) {
      fs::current_path(fs::current_path()/"build"/"bin");
      filesystem::execCommandQuiet(std::format("./{}", projectName).c_str());
      return 0;
    }

    printColor("Running project...\n", color::green);

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
    nlohmann::json projectInfo = nlohmann::json::parse(f);
    std::string name = projectInfo["releaseName"];
    std::string desc = projectInfo["description"];
    std::string ver = projectInfo["ver"];
    printColor(std::format("Name: {}\n" ,name), color::white);
    printColor(std::format("Description: {}\n" ,desc), color::white);
    printColor(std::format("Version: {}\n" ,ver), color::white);
  } 

  return true;
}








