#include "../../engine/vendored/argparse/include/argparse/argparse.hpp"

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
  projectBuild.add_argument("--release")
    .default_value(false)
    .implicit_value(true);
  projectBuild.add_argument("--debug")
    .default_value(false)
    .implicit_value(true);
  argparse::ArgumentParser projectRun("run");
  projectRun.add_argument("projectName");
  projectRun.add_argument("--suppress")
    .default_value(false)
    .implicit_value(true);
  argparse::ArgumentParser projectInfo("info");
  projectInfo.add_argument("projectName");
  argparse::ArgumentParser projectCreate("create");
  projectCreate.add_argument("projectName");
  argparse::ArgumentParser projectRemove("remove");
  projectRemove.add_argument("projectName");
  argparse::ArgumentParser projectList("list");

  projectParser.add_subparser(projectRemove);
  projectParser.add_subparser(projectList);
  projectParser.add_subparser(projectCreate);
  projectParser.add_subparser(projectBuild);
  projectParser.add_subparser(projectRun);
  projectParser.add_subparser(projectInfo);

  // Engine Parsing
  argparse::ArgumentParser engineParser("engine");
  argparse::ArgumentParser engineBuild("build");
  engineBuild.add_argument("--release")
    .default_value(false)
    .implicit_value(true);
  engineBuild.add_argument("--debug")
    .default_value(false)
    .implicit_value(true);
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

      if (fs::exists(fs::current_path()/"build")) {
        fs::remove_all(fs::current_path()/"build");
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

        if (fs::exists(fs::current_path()/"build")) {
          fs::remove_all(fs::current_path()/"build");
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


