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

#include "parser.hpp"
#include "context/contextParser.hpp"
#include "project/projectParser.hpp"
#include "engine/engineParser.hpp"
#include "../common/common.hpp"

using namespace secret;
using namespace output;
using namespace filesystem;
using namespace parser;

using json = nlohmann::json;

int main(int argc, char *argv[]) {

  locateToEngineRoot(); 

  ProgramParser program;
  ProjectParser projectParser;
  EngineParser engineParser;
  ContextParser contextParser;

  program.program.add_subparser(projectParser.projectParser);
  program.program.add_subparser(engineParser.engineParser);
  program.program.add_subparser(contextParser.contextParser);

  try {
    program.program.parse_args(argc, argv);
  }
  catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program.program;
    return 1;
  }

  // parse arguments

  if (program.program.is_subcommand_used("project")) {
    projectParser.parseArguments();
  }
  if (program.program.is_subcommand_used("context")) {
    contextParser.parseArguments();
  }
  if (program.program.is_subcommand_used("engine")) {
    engineParser.parseArguments();
  }

}




