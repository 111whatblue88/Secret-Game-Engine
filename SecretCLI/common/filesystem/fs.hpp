#ifndef _FS_HPP_
#define _FS_HPP_

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace secret {
namespace filesystem {

void execCommand(const char* cmd);

void locateToEngineRoot();

}
}

#endif 
