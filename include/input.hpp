#ifndef _INPUT_H
#define _INPUT_H

#include <string>
#include <vector>

class in {
public:

    static std::vector<std::string> tokenize(std::string inString);

    static void getInput(std::string& inString);

};

#endif