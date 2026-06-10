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
  argparse::ArgumentParser projectParser("projectParser");


  // Add all parsers to main parser 
  program.add_subparser(projectParser);


  try {
    program.parse_args(argc, argv);
  }
  catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  if (program.is_subcommand_used("projectParser")) {

  } 

}


