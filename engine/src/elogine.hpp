#ifndef _ELOGINE_HPP
#define _ELOGINE_HPP

#include "terminal/input.hpp"
#include "terminal/output.hpp"
#include "rendering/render.hpp"
#include "utils/utils.hpp"


#include <string>

namespace elo {

    class elogine {
    public:

        elogine(std::string name, float width, float height, int targetFPS);
        ~elogine();

        bool m_quit;

        RenderContext m_mainContext;

        bool run();

    };


}

#endif 



