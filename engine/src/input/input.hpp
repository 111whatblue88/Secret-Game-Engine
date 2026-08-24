#ifndef _INPUT_HPP
#define _INPUT_HPP

#include "../general/general.hpp"
#include <SDL3/SDL.h>
#include "../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../../vendored/SDL/src_mixer/include/SDL3_mixer/SDL_mixer.h"
namespace secret {
namespace input {

  class InputSys {

  public:
    InputSys();
    enum class KeyState {
      RELEASED, PRESSED, HELD, NONE
    };
    
    static bool Input();
    static bool quit;

    static bool hideMouse(bool state);

    static Vec2 mousePos;

  private:
    static SDL_Event m_input;
    static void resetKey(KeyState& key);
    struct Keys {

      KeyState W;
      KeyState A;
      KeyState S;
      KeyState D;

      KeyState P;

      KeyState I;
      KeyState K;

      KeyState num2;
      KeyState num1;

      KeyState ESC;

      KeyState mouseRight;
      KeyState mouseLeft;

    };
  public:
    static Keys keys;
  }; 

}
}

#endif






