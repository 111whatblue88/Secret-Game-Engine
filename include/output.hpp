#ifndef _OUTPUT_H
#define _OUTPUT_H

#include <string>

class out {
public:

    enum class mesgType {
        error, normal, warning
    };

    enum class color {
        red, blue, green, white, yellow
    };

    static void send(std::string inString, mesgType inType);

    static std::string colorString(std::string inString, color inColor);
   
    static void clearScreen();    

};




#endif












