#ifndef _ELOGINE_HPP
#define _ELOGINE_HPP

#include "rendering/render.hpp"
#include "utils/utils.hpp"


#include <string>

namespace elo {

    class elogine {
    public:

        elogine(std::string name, float width, float height, int targetFPS);
        ~elogine();

        bool m_quit;

        renderContext m_mainContext;

        bool run();

    };


}

#endif 



