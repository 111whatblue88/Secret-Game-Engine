#ifndef _INPUT_HPP
#define _INPUT_HPP

#include <string>
#include <vector>

namespace elo {

    class TermInput {
    public:

        static std::string getInput();
        static std::string getInput(std::string inString);

        static std::vector<std::string> tokenize(std::string inString);

    };

}


#endif