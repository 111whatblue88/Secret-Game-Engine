
#include "../../engine/src/elogine.hpp"

#include <iostream>
#include <string>
#include <vector>

void printSplash();

void printHelp();

void proccessTokens(std::vector<std::string> inTokens);

int main() {

    using namespace elo;

    std::string ans;

    printSplash();

    do {

        ans = TermInput::getInput(TermOutput::colorString("waiting for input: ", TermOutput::Color::white));

    } while (ans != "quit" && ans != "exit");


}

/*
 ________  _____       ___            _                  
|_   __  ||_   _|    .'   `.         (_)                 
  | |_ \_|  | |     /  .-.  \ .--./) __   _ .--.  .---.  
  |  _| _   | |   _ | |   | |/ /'`\;[  | [ `.-. |/ /__\\ 
 _| |__/ | _| |__/ |\  `-'  /\ \._// | |  | | | || \__., 
|________||________| `.___.' .',__` [___][___||__]'.__.' 
   ______  _____     _____  ( ( __))                     
 .' ___  ||_   _|   |_   _|                              
/ .'   \_|  | |       | |                                
| |         | |   _   | |                                
\ `.___.'\ _| |__/ | _| |_                               
 `.____ .'|________||_____|                              

*/


void printSplash() {

    elo::TermOutput::clear();

    std::cout << " ________  _____       ___            _                  \n";
    std::cout << "|_   __  ||_   _|    .'   `.         (_)                 \n";
    std::cout << "  | |_ \\_|  | |     /  .-.  \\ .--./) __   _ .--.  .---.  \n";
    std::cout << "  |  _| _   | |   _ | |   | |/ /'`\\;[  | [ `.-. |/ /__\\ \n";
    std::cout << " _| |__/ | _| |__/ |\\  `-'  /\\ \\._// | |  | | | || \\__., \n";
    std::cout << "|________||________| `.___.' .',__` [___][___||__]'.__.' \n";
    std::cout << "   ______  _____     _____  ( ( __))                     \n";
    std::cout << " .' ___  ||_   _|   |_   _|                              \n";
    std::cout << "/ .'   \\_|  | |       | |                                \n";
    std::cout << "| |         | |   _   | |                                \n";
    std::cout << "\\ `.___.'\\ _| |__/ | _| |_                               \n";
    std::cout << " `.____ .'|________||_____|                              \n\n";
    std::cout << "ELOgine Ver. 0.1-ALPHA\n";
    std::cout << "type \"helpe\" for a list of commands\n\n";
}



