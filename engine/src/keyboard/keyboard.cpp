
#include "keyboard.hpp"
#include "../elogine.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>


namespace engine{
namespace input {

bool InputSys::Input() {

  resetKey(keys.W); 
  resetKey(keys.A); 
  resetKey(keys.S); 
  resetKey(keys.D); 

  while (SDL_PollEvent(&m_input)) {

    switch (m_input.type) {
    
      case SDL_EVENT_QUIT: {
        quit = true;
        break;
      }
      case SDL_EVENT_KEY_DOWN: {
        switch (m_input.key.key) {
          case SDLK_W: 
            keys.W = KeyState::PRESSED;
            break;
          case SDLK_A: 
            keys.A = KeyState::PRESSED;
            break;
          case SDLK_S: 
            keys.S = KeyState::PRESSED;
            break;
          case SDLK_D: 
            keys.D = KeyState::PRESSED;
            break;
        }
        break;
      }
      case SDL_EVENT_KEY_UP: {
        switch (m_input.key.key) {
          case SDLK_W: 
            keys.W = KeyState::RELEASED;
            break;
          case SDLK_A: 
            keys.A = KeyState::RELEASED;
            break;
          case SDLK_S: 
            keys.S = KeyState::RELEASED;
            break;
          case SDLK_D: 
            keys.D = KeyState::RELEASED;
            break;
        }
        break;
      }

      default: {
      
      }

    }

  }


  return true;
}

void InputSys::resetKey(InputSys::KeyState& key) {
  switch (key) {
    case InputSys::KeyState::PRESSED: {
      key = InputSys::KeyState::HELD;
      break;
    }
    case InputSys::KeyState::RELEASED: {
      key = InputSys::KeyState::NONE;
      break; 
    }

  }

};

InputSys::InputSys() {
  quit = false;
}

}
}

