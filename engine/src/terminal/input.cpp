
#include "../elogine.hpp"

#include <sstream>
#include <iostream>
#include <vector>
#include <string>

namespace elo {

    std::string TermInput::getInput() {

        std::string ans;

        std::cout << "waiting for input: ";
        std::getline(std::cin, ans);

        return ans;

    }

    std::string TermInput::getInput(std::string inString) {

        std::string ans;

        std::cout << inString;
        std::getline(std::cin, ans);

        return ans;

    }

    std::vector<std::string> TermInput::tokenize(std::string inString) {


        std::vector<std::string> tokens;
        std::string token;

        std::stringstream stream(inString);

        while (stream >> token) {
            tokens.push_back(token);
        }

        return tokens;

    }

}


