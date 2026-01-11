#ifndef _INPUT_HPP
 
  #include <string>
  #include <vector>

  namespace elogine {
  namespace terminal {
  class Input {
  public:

    static std::string getInput(std::string prompt);
    static std::vector<std::string> tokenize(std::string input);

  };
  }
  }

#endif 
