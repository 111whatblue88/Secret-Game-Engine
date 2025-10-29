#ifndef _KEYS_H
#define _KEYS_H

#include <SDL3/SDL.h>

class Input {
public:

    static void init();

    static void scanInput(SDL_Event input);

    static void resetKeys();

    enum class keyState {
        pressed, released, none, held
    };

    static keyState wKey;
    static keyState aKey;
    static keyState sKey;
    static keyState dKey;
    static keyState spaceKey;

};

#endif