#include "../../engine/vendored/argparse/include/argparse/argparse.hpp"

#include <complex>
#include <cstdio>
#include <iostream>
#include <memory>
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

using json = nlohmann::json;

void execCommand(const char* cmd) {
  std::string command = std::format("{} 2>&1", cmd);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return;
    }

    std::array<char, 256> buffer;

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        std::cout << buffer.data();
        std::cout.flush();
    }

    int status = pclose(pipe);

    return;
}

int main(int argc, char *argv[]) {

  std::ifstream f("../../cliInfo.json");
  json cliInfo = json::parse(f);

  argparse::ArgumentParser program("SecretCLI", cliInfo["ver"]);

  // project command
  argparse::ArgumentParser projectParser("project");
  projectParser.add_description("For building and managing Secret projects");

  argparse::ArgumentParser projectBuild("build");
  projectBuild.add_argument("projectName")
    .help("Builds the given project name, if it exists");

  argparse::ArgumentParser projectRun("run");
  projectRun.add_argument("projectName")
    .help("Runs the given project name, if it exists");


  // attach subparsers to project command
  projectParser.add_subparser(projectBuild);
  projectParser.add_subparser(projectRun);

  program.add_subparser(projectParser);

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  if (program.is_subcommand_used("project")) {
    if (projectParser.is_subcommand_used("build")) {
      std::string name = projectBuild.get<std::string>("projectName");
      execCommand(std::format("../../CLIScripts/buildProject.sh {}", name).c_str());
    }
    if (projectParser.is_subcommand_used("run")) {
      std::string name = projectRun.get<std::string>("projectName");
      execCommand(std::format("../../CLIScripts/runProject.sh {}", name).c_str());
    }
  }
  

}


