#ifndef TEXT
#define TEXT

#include "../include/ELOgine.hpp"

#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class Text {
private:
    struct TextData {
        std::string id;
        SDL_Texture* textTexture;
        SDL_FRect destination;
    };

    static std::vector<TextData> TextInstances;

public:

    bool static pushInstance(SDL_Renderer* renderer, SDL_FRect inDestination, std::string location, float size, std::string text, SDL_Color inColor, std::string id);

    bool static remInstance(std::string id);

    bool static renderInstances(SDL_Renderer* renderer);

    bool static moveText(int x, int y, std::string id);

};

#endif