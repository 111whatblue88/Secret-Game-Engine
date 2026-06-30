#ifndef _PROJECTPARSER_HPP
#define _PROJECTPARSER_HPP

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

#include "../../common/common.hpp"

namespace secret { namespace parser {

class ProjectParser {
public:

  ProjectParser(); 

  argparse::ArgumentParser projectParser;

  argparse::ArgumentParser projectBuild;
  argparse::ArgumentParser projectRun;
  argparse::ArgumentParser projectInfo;
  argparse::ArgumentParser projectCreate;
  argparse::ArgumentParser projectRemove;
  argparse::ArgumentParser projectList;

  bool parseArguments();

private:
};

}}

#endif

