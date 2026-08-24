#include <filesystem>
#include <iostream>
#include <string>
#include <format>

#include "../secret.hpp"

namespace fs = std::filesystem;

using namespace secret;
using namespace filesystem;

void filesystem::execCommand(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
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
    if (std::filesystem::exists("engine")) {
      fs::current_path(fs::current_path()/"engine");
      return;
    }
    fs::current_path("..");
  }
}
