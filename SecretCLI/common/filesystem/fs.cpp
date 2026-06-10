#include <filesystem>
#include <iostream>
#include <string>
#include <format>

#include "fs.hpp"

namespace fs = std::filesystem;

using namespace secret;
using namespace filesystem;

void filesystem::execCommand(const char* cmd) {
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

void filesystem::locateToEngineRoot() {
  while (true) {
    if (fs::current_path() == "Secret Game Engine") {
      return;
    }
    fs::current_path("../");
  }
}
