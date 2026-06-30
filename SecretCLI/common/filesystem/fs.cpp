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

#include "fs.hpp"

namespace fs = std::filesystem;

using namespace secret;
using namespace filesystem;

void filesystem::execCommandQuiet(const char* cmd) {
  std::string command = std::format("{} 2>&1", cmd);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return;
    }

    std::array<char, 256> buffer;

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {

    }

    int status = pclose(pipe);

    return;
}

void filesystem::execCommand(const char* cmd) {
  std::string command = std::format("stdbuf -oL {} 2>&1", cmd);
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
    if (fs::current_path().filename() == "Secret-Game-Engine") {
      return;
    }
    fs::current_path("..");
  }
}

nlohmann::json filesystem::fetchCLIInfo() {
  locateToEngineRoot(); 
  return nlohmann::json::parse(std::ifstream("SecretCLI/cliInfo.json"));
}
nlohmann::json filesystem::fetchEngineInfo() {
  locateToEngineRoot(); 
  return nlohmann::json::parse(std::ifstream("engine/engineInfo.json"));
}

