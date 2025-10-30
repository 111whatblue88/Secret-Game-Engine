#ifndef _ELOGINE_HPP
#define _ELOGINE_HPP

#include "rendering/render.hpp"

#include <string>

namespace elo {

    class elogine {
    public:

        elogine(std::string name, float width, float height);
        ~elogine();

        bool m_quit;

        renderContext m_mainContext;

        bool run();

    };


}

#endif 



