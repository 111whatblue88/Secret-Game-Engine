#ifndef _PARSER_HPP
#define _PARSER_HPP

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

#include "../common/common.hpp"

namespace secret { namespace parser {

class ProgramParser {
public:

  ProgramParser(); 

  argparse::ArgumentParser program;

private:
};

}}

#endif


