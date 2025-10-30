
--struct for important SDL stuff, like windows and whatnot

namespace elo {

    struct renderContext {

        renderContext(std::string inName, float inWidth, float inHeight)
            : M_WINDOW_WIDTH(inWidth), M_WINDOW_HEIGHT(inHeight)
        {
            m_window = SDL_CreateWindow(inName, M_WINDOW_WIDTH, M_WINDOW_HEIGHT);
            m_renderer = SDL_CreateRenderer(m_window);
        }

        const float M_WINDOW_WIDTH;
        const float M_WINDOW_HEIGHT;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        ~renderContext() {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
        }

    }


}


--main elogine class that handles a lot of the dirty work

maybe in a namespace "elo"

namespace elo {

    class elo {

        bool m_quit;

        renderContext mainContext;

        elo(std::string windowName, float width, float height)
            : m_quit(false)
        {

            SDL_init(); do checks for if it ran correctly
            TTF_init();

            renderContext mainContext(windowName, width, height); 

        }

        bool run { this is what you would call to start the game loop

            while !(m_quit) { 

                start frame counter

                input check

                update game objects

                render

                delay with frame counter logic

            }

            return true;

        }


    } the amount of brakets will go down as these will be defined in different files

}





