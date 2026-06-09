#include "../HUGE.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>


namespace huge {
namespace input {

InputSys::Keys InputSys::keys = {

  KeyState::NONE, 
  KeyState::NONE, 
  KeyState::NONE, 
  KeyState::NONE, 

  KeyState::NONE, 

  KeyState::NONE, 
  KeyState::NONE, 
  KeyState::NONE, 
  KeyState::NONE, 
  KeyState::NONE, 
};

SDL_Event InputSys::m_input = SDL_Event();

bool InputSys::Input() {

  resetKey(keys.W); 
  resetKey(keys.A); 
  resetKey(keys.S); 
  resetKey(keys.D); 
  resetKey(keys.P); 
  resetKey(keys.ESC); 
  resetKey(keys.I); 
  resetKey(keys.K); 

  resetKey(keys.num1); 
  resetKey(keys.num2); 

  while (SDL_PollEvent(&m_input)) {

    switch (m_input.type) {
    
      case SDL_EVENT_QUIT: {
        console::COutput::logCustom("INPUT", "OS quit key given, exiting");
        core::Engine::exit();
        break;
      }
      case SDL_EVENT_KEY_DOWN: {
        switch (m_input.key.key) {
          case SDLK_1: 
            keys.num1 = KeyState::PRESSED;
            break;
          case SDLK_2: 
            keys.num2 = KeyState::PRESSED;
            break;

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
          case SDLK_P: 
            keys.P = KeyState::PRESSED;
            break;
          case SDLK_I: 
            keys.I = KeyState::PRESSED;
            break;
          case SDLK_K: 
            keys.K = KeyState::PRESSED;
            break;

          case SDLK_ESCAPE: 
            keys.ESC = KeyState::PRESSED;
            break;
        }
        break;
      }
      case SDL_EVENT_KEY_UP: {
        switch (m_input.key.key) {

          case SDLK_1: 
            keys.num1 = KeyState::RELEASED;
            break;
          case SDLK_2: 
            keys.num2 = KeyState::RELEASED;
            break;

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
          case SDLK_P: 
            keys.P = KeyState::RELEASED;
            break;
          case SDLK_I: 
            keys.I = KeyState::RELEASED;
            break;
          case SDLK_K: 
            keys.K = KeyState::RELEASED;
            break;
          case SDLK_ESCAPE: 
            keys.ESC = KeyState::RELEASED;
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


}
}



