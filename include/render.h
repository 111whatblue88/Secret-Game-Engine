#ifndef _RENDER_H
#define _RENDER_H

#include <SDL3/SDL.h>

class Image {
public:

    Image();
    Image(const char *imgLocation, SDL_Renderer *renderer, float x, float y, float w, float h);
    ~Image();

    SDL_FRect pos;

    bool init(const char *imgLocation, SDL_Renderer *renderer, float x, float y, float w, float h);
    void render(SDL_Renderer *renderer);

private:

    SDL_Texture *texture;
    
};

#endif