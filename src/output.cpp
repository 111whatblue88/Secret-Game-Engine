#include "../include/ELOgine.hpp"
#include <string>
#include <iostream>

void out::send(std::string inString, mesgType inType) {

    std::string outType;

    switch (inType)
    {
    case mesgType::error:
        outType = "\033[1;31m[ERROR]\033[1;37m "; 
        break;

    case mesgType::normal:
        outType = "\033[1;37m[MESSAGE]\033[1;37m "; 
        break;
        

    case mesgType::warning:
        outType = "\033[1;33m[WARNING]\033[1;37m "; 
        break;
    }

    std::cout << outType << inString << "\033[0m" << "\n";

}

std::string out::colorString(std::string inString, color inColor) {

    std::string outString;

    switch (inColor) {

        case color::red: {
            outString = "\033[1;31m" + inString + "\033[0m";
            return outString;
        }
        case color::green: {
            outString = "\033[1;32m" + inString + "\033[0m";
            return outString;
        }
        case color::blue: {
            outString = "\033[1;34m" + inString + "\033[0m";
            return outString;

        }
        case color::white: {
            outString = "\033[1;37m" + inString + "\033[0m";
            return outString;
        }
        case color::yellow: {
            outString = "\033[1;33m" + inString + "\033[0m";
            return outString;
        }

    }

    return "\033[1;31m[ERROR] colorString failed\n\033[0m";

}

void out::clearScreen() {

    std::cout << "\033[2J\033[H";

}

