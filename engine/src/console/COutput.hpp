#ifndef _CINPUT_HPP_
#define _CINPUT_HPP_

#include <string>

namespace secret {
namespace console {

class COutput {
public:

  static void LogError(std::string system, std::string errMsg);
  static void LogWarning(std::string system, std::string warMsg);
  static void Log(std::string system, std::string msg);

  static void LogDescriptive(std::string system, std::string msg);

  static void LogSDLError();

};

}
}


#endif 
