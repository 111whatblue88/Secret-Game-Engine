#ifndef _KEYBOARD_HPP
#define _KEYBOARD_HPP

#include <SDL3/SDL_events.h>
namespace engine{
namespace input {

  class InputSys {

  public:
    InputSys();
    enum class KeyState {
      RELEASED, PRESSED, HELD, NONE
    };
    
    bool Input();

    bool quit;
  private:
    SDL_Event m_input;
    void resetKey(KeyState& key);
    struct Keys {

      KeyState W;
      KeyState A;
      KeyState S;
      KeyState D;

    };
  public:
    Keys keys;
  }; 

}
}




#endif

