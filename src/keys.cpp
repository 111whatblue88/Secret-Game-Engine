
#include "../include/ELOgine.hpp"

#include <iostream>
#include <SDL3/SDL.h>

Input::keyState Input::wKey = Input::keyState::none;
Input::keyState Input::aKey = Input::keyState::none;
Input::keyState Input::sKey = Input::keyState::none;
Input::keyState Input::dKey = Input::keyState::none;
Input::keyState Input::spaceKey = Input::keyState::none;

void Input::scanInput(SDL_Event input) {

    switch (input.type)
    {
    case SDL_EVENT_KEY_DOWN:
        switch (input.key.key)
        {
        case SDLK_W:
            wKey = keyState::pressed;
            break;
        case SDLK_A:
            aKey = keyState::pressed;
            break;

        case SDLK_S:
            sKey = keyState::pressed;
            break;
        case SDLK_D:
            dKey = keyState::pressed;
            break;
        case SDLK_SPACE:
            spaceKey = keyState::pressed;
            break;
        }
        break;
    case SDL_EVENT_KEY_UP:
        switch (input.key.key)
        {
        case SDLK_W:
            wKey = keyState::released;
            break;
        
        case SDLK_A:
            aKey = keyState::released;
            break;

        case SDLK_S:
            sKey = keyState::released;
            break;
        case SDLK_D:
            dKey = keyState::released;
            break;

        case SDLK_SPACE:
            spaceKey = keyState::pressed;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

}

void Input::resetKeys() {

    if (wKey == keyState::pressed) wKey = keyState::held;
    if (aKey == keyState::pressed) aKey = keyState::held;
    if (sKey == keyState::pressed) sKey = keyState::held;
    if (dKey == keyState::pressed) dKey = keyState::held;
    if (spaceKey == keyState::pressed) spaceKey = keyState::held;

    if (wKey == keyState::released) wKey = keyState::none;
    if (aKey == keyState::released) aKey = keyState::none;
    if (sKey == keyState::released) sKey = keyState::none;
    if (dKey == keyState::released) dKey = keyState::none;
    if (spaceKey == keyState::released) spaceKey = keyState::none;
}