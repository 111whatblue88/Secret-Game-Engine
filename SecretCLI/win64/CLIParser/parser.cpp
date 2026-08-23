#include "../../../engine/vendored/argparse/include/argparse/argparse.hpp"

#include <algorithm>
#include <complex>
#include <cstdio>
#include <iostream>
#include <memory>
#include "../../../engine/vendored/json/single_include/nlohmann/json.hpp"
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

#include "parser.hpp"
#include "../common/common.hpp"

using namespace secret;
using namespace parser;

ProgramParser::ProgramParser()
  :program("SecretCLI", filesystem::fetchCLIInfo()["ver"])
{}

