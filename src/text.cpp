
#include "../include/ELOgine.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

std::vector<Text::TextData> Text::TextInstances;

bool Text::pushInstance(SDL_Renderer* renderer, SDL_FRect inDestination, std::string location, float size, std::string text, SDL_Color inColor, std::string id) {

    TTF_Font* newText;
    newText = TTF_OpenFont(location.c_str(), size);

    if (!newText) {

        out::send("font location not found, falling back...", out::mesgType::error);
        out::send(SDL_GetError(), out::mesgType::error);

        newText = TTF_OpenFont("../../assets/fallbacks/fonts/JetBrainsMono-Regular.ttf", size);

        if (!newText) {
            out::send("fallback font not found", out::mesgType::error);
            out::send(SDL_GetError(), out::mesgType::error);
            return false;
        }
    }

    SDL_Surface* tempSurface = TTF_RenderText_Solid(newText, text.c_str(), 0, inColor);
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_DestroySurface(tempSurface);
    TTF_CloseFont(newText);
   
    if (!newTexture) {
        out::send("text texture did not create properly", out::mesgType::error);
        out::send(SDL_GetError(), out::mesgType::error);
        return false;
    }  

    TextData outData;
    outData.destination = inDestination;
    outData.textTexture = newTexture;
    outData.id = id;

    TextInstances.push_back(outData); 

    return true;

}


bool Text::renderInstances(SDL_Renderer* renderer) {

    for (size_t i = 0; i < TextInstances.size(); i++) {

        if (!SDL_RenderTexture(renderer, TextInstances[i].textTexture, NULL, &TextInstances[i].destination)) {
            out::send("text texture did not render properly", out::mesgType::error);
            out::send(SDL_GetError(), out::mesgType::error);
            return false;
        }

    }

    return true;

}

bool Text::remInstance(std::string id) {

    for (size_t i = 0; i < TextInstances.size(); i++) {

        if (TextInstances[i].id == id) {
            SDL_DestroyTexture(TextInstances[i].textTexture); 
            TextInstances[i] = TextInstances.back();
            TextInstances.pop_back();
            return true;
        }

    }

    return false;

}

bool Text::moveText(int x, int y, std::string id) {

    for (size_t i = 0; i < TextInstances.size(); i++) {

        if (TextInstances[i].id != id) {
            continue;
        } 
        TextInstances[i].destination.x = x;
        TextInstances[i].destination.y = y;
        return true;

    }

    return false;

}
