#ifndef _OUTPUT_HPP
 
  #include <iostream>
  #include <string>

  namespace elogine {
  namespace terminal {
  class Output {
  public:

    enum class LogLevel {
      normal, warning, error
    };
    enum class Color {
      red, green, yellow, blue, white
    };
    
    static void log(std::string message, LogLevel logLevel);
    static std::string colorString(std::string inString, Color color);

    static void clearTerminal();

  };
  }
  }

#endif 
