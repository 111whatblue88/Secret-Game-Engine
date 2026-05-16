#ifndef _CINPUT_HPP_
#define _CINPUT_HPP_

#include <string>

namespace huge {
namespace console {

class COutput {
public:
  enum class MsgColor {
    red, green, yellow, white, reset
  };

  static void logError(std::string errMsg);
  static void logWarning(std::string warMsg);
  static void log(std::string msg);

  static void log(std::string, MsgColor color);

  static void logSDLError();

  static void logCustom(std::string header, std::string msg, MsgColor color);
  static void logCustom(std::string header, std::string msg);
private:
  static std::string resolveColor(MsgColor color);
};

}
}


#endif 
