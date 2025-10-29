#include "../include/ELOgine.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include <iostream>

Image::Image(const char *imgLocation, SDL_Renderer *renderer, float x, float y, float w, float h) {

    init(imgLocation, renderer, x, y, w, h);

}

Image::Image() {

}

bool Image::init(const char *imgLocation, SDL_Renderer *renderer, float x, float y, float w, float h) {

    pos = {x, y, w, h};

    //free this to print working directory
    //std::cout << std::filesystem::current_path() << "\n";

    texture = IMG_LoadTexture(renderer, imgLocation);
    if (!texture) {
        out::send(SDL_GetError(), out::mesgType::error);
        out::send("Falling back to default texture...", out::mesgType::error);
        texture = IMG_LoadTexture(renderer, "../../assets/fallbacks/textures/default.png");
        if (!texture) {
            out::send(SDL_GetError(), out::mesgType::error);
            out::send("Fallback failed!", out::mesgType::error);
        }
        return false;
    }

    return true;

}

Image::~Image() {

    SDL_DestroyTexture(texture);

}

void Image::render(SDL_Renderer *renderer) {

    SDL_RenderTexture(renderer, texture, NULL, &pos);

}
