#ifndef _PT_HPP_
#define _PT_HPP_

#include <string>

namespace secret {
namespace helpers {
 
  enum class color {
    red, green, blue, white
  };

  void printColor(std::string string, color color);
  void clearTerm();
  void printSplash(color color);

}
}

#endif



