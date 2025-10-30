
#include "../elogine.hpp"

#include <iostream>
#include <string>

namespace elo {

    std::string TermOutput::colorString(std::string inString, Color inColor) {

        switch (inColor) {

            case Color::red: {
                return "\033[1;31m"+inString+"\033[0m";
                break;
            }
            case Color::green: {
                return "\033[1;32m"+inString+"\033[0m";
                break;
            }
            case Color::blue: {
                return "\033[1;34m"+inString+"\033[0m";
                break;
            }
            case Color::yellow: {
                return "\033[1;33m"+inString+"\033[0m";
                break;
            }
            case Color::white: {
                return "\033[1;37m"+inString+"\033[0m";
                break;
            }


        }

    }

    void TermOutput::outputStyle(std::string inString, StyleType inStyle) {

        switch (inStyle) {

            case StyleType::message: {
                std::cout << "\033[1;37m[MESSAGE] "+inString+"\n\033[0m";
                break;
            }
            case StyleType::waring: {
                std::cout << "\033[1;33m[WARNING] "+inString+"\n\033[0m";
                break;
            }
            case StyleType::error: {
                std::cout << "\033[1;31m[ERROR] "+inString+"\n\033[0m";
                break;
            }
        }

    }





    void TermOutput::clear() {
        std::cout << "\033[2J\033[H";
    }




}

