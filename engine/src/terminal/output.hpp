#ifndef _OUTPUT_HPP
#define _OUTPUT_HPP

#include <string>

namespace elo {

    class TermOutput {
    public:

        enum class Color {
            red, green, blue, yellow, white
        };

        enum class StyleType {
            message, waring, error
        };

        static std::string colorString(std::string inString, Color inColor);

        static void outputStyle(std::string inString, StyleType inStyle);

        static void clear();

    };

}

#endif