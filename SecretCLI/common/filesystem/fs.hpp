#ifndef _FS_HPP_
#define _FS_HPP_


#include <format>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <nlohmann/json.hpp>

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace secret {
namespace filesystem {


void execCommandQuiet(const char* cmd);
void execCommand(const char* cmd);

void locateToEngineRoot();

nlohmann::json fetchCLIInfo();
nlohmann::json fetchEngineInfo();

}
}

#endif 
