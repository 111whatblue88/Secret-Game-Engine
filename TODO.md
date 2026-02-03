
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

namespace elo {

    class elogine {

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

RENDERING SYSTEM

bool render() {

  clear screen 

  
  for (loop stuff) {
  
  if (entity->rendEnabled) {
  
    entity->renderingComp->render(); 

  }

  }

  present screen  
    
}

ECS 

namespace elo {

class entity {

  int x, int y;

  //rendering
  bool rendEnabled
  renderingComp rendComp;

  


}

class renderingComp {

  public:
  void changeImage(std::string imagePath); <- this destroys the old one and creates a new texture with the given image
  SDL_Struct imageLocation;
  private:
  friend class elogine
  void render(sdl renderer); <- this just renders the texture at imageLocation
  sdl_texture texture;

};


-- in the elogine class:

class elogine {

  std::vector<std::unique_ptr<entity>> entityVector; <- use unique pointers here

  void addEntity(std::unique_ptr<entity>) {

  entityVector.push_back(std::move(entity)) 
  


  }

}

KEYBOARD INPUT 

namespace INPUT {

class InputSys {
public:

  Input()

  enum class KeyState {
    down, up, none, held
  }

  

private:

  struct keys {
    keystate keya 
    keystate keyb 
    etc
  }

}

}

if (inpussys.key.a == inputsys.keystate::held)



NEXT:

add a rigidBody component, add a player controller component
make sure to add the rigidbody update in the collision detection 




