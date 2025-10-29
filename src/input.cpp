
#include "../include/ELOgine.hpp"

#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>


void in::getInput(std::string& inString) {

    std::cout << out::colorString("Waiting for input: ", out::color::white);
    std::getline(std::cin, inString);

}

std::vector<std::string> in::tokenize(std::string inString) {

    std::vector<std::string> tokens;
    std::string token;

    std::stringstream stream(inString);
    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;

}
