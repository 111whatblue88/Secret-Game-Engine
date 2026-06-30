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

#include "contextParser.hpp"
#include "../../common/common.hpp"

using namespace secret;
using namespace parser;
using namespace output;
using namespace filesystem;


ContextParser::ContextParser():
  contextParser("context", " "),
  contextClear("clear", " "),
  contextProject("project", " ")
{
  
  contextParser.add_description("adds context to shorten command verbosity");
  contextClear.add_description("clears the current context");
  contextProject.add_description("changes the context to be assume a project is being referenced");

  contextProject.add_argument("projectName");

  contextParser.add_subparser(contextClear);
  contextParser.add_subparser(contextProject);

}

bool ContextParser::parseArguments() {

  if (contextParser.is_subcommand_used("clear")) {
    locateToEngineRoot();
    std::ifstream f("SecretCLI/cliInfo.json");
    nlohmann::json cliInfo = nlohmann::json::parse(f);
    cliInfo["context"]["project"] = "";

    std::ofstream cliInfoFile("SecretCLI/cliInfo.json");
    cliInfoFile << cliInfo.dump(2);
    cliInfoFile.close();
    printColor("Context cleared\n", color::green);
  }
  if (contextParser.is_subcommand_used("project")) {
    std::string projectName = contextProject.get("projectName");
    locateToEngineRoot();
    std::ifstream cliInfoFileREAD("SecretCLI/cliInfo.json");
    nlohmann::json cliInfo = nlohmann::json::parse(cliInfoFileREAD);
    cliInfoFileREAD.close();

    if (!fs::exists(fs::current_path()/"projects")) {
      printColor("No projects.. Use \"project create {NAME}\" to create a project\n", color::red);
      return 1;
    }
    if (!fs::exists(fs::current_path()/"projects"/projectName)) {
      printColor("Given project does not exist\n", color::red);
      return 1;
    }

    cliInfo["context"]["project"] = projectName;

    std::ofstream cliInfoFileWRITE("SecretCLI/cliInfo.json");
    cliInfoFileWRITE << cliInfo.dump(2);
    cliInfoFileWRITE.close();
    printColor("Context changed\n", color::green);

  }

  return true;
}








