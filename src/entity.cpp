
#include "../include/ELOgine.hpp"

#include <SDL3/SDL.h>
#include <iostream>

Health::Health() {
    maxHealth = 100;
    health = 100;
}

void Health::init(float x, float y, float  w, float h, int setMaxHealth) {

    underBar = {x, y, w, h};
    overBar = {x, y, w, h};

}

void Health::render(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &underBar);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &overBar);

}

void Health::editHealth(int amount) {
    
    health += amount;

    if (health < 0) {
        health = 0;
    }
    if (health > maxHealth) {
        health = maxHealth;
    }
    
    overBar.w = (health * underBar.w) / maxHealth;

}

void Entity::initBase(float x, float y, float w, float h, float inSpeed) {

    generalCollisionEnabled = false;
    gravityEnabled = false;
    jumpEnabled = false;

    hitboxTweakX = 0;
    hitboxTweakY = 0;
    hitboxTweakW = 0;
    hitboxTweakH = 0;

    xUpperBounds = 0;
    yUpperBounds = 0;
    xLowerBounds = 0;
    yLowerBounds = 0;

    speed = inSpeed;
    pos = {x, y, w, h};
    Hitbox = {x, y, w, h};

}

void Entity::autoUpdateDir() {

    int x = 0, y = 0;

    if (Input::wKey == Input::keyState::held) y--;
    if (Input::aKey == Input::keyState::held) x--;
    if (Input::sKey == Input::keyState::held) y++;
    if (Input::dKey == Input::keyState::held) x++;

    // general collision check
    if (generalCollisionEnabled) {
        if (Hitbox.x <= xLowerBounds && x == -1) x++; 
        if ((Hitbox.x + Hitbox.w) >= xUpperBounds && x == 1) x--; 
        if (Hitbox.y <= yLowerBounds && y == -1) y++; 
        if ((Hitbox.y + Hitbox.h) >= yUpperBounds && y == 1) y--; 
    }

    if (jumpEnabled) {
        if (y == -1) y++;
    }

    if (x == -1 && y == 0) currentDir = dir::left; else if
    (x == 1 && y == 0) currentDir = dir::right; else if
    (x == 0 && y == -1) currentDir = dir::up; else if
    (x == 0 && y == 1) currentDir = dir::down; else if
    (x == 0 && y == 0) currentDir = dir::none;
    
}

void Entity::updateDir(dir inDir) {
    currentDir = inDir;
}


void Entity::move() {

    switch (currentDir)
    {
    case dir::up:
        pos.y -= speed;
        break;
    case dir::down:
        pos.y += speed;
        break;
    case dir::right:
        pos.x += speed;
        break;
    case dir::left:
        pos.x -= speed;
        break;
    case dir::none:
        break;
    }

    if (gravityEnabled) {
        if (generalCollisionEnabled) {
            if ((Hitbox.y + Hitbox.h) >= yUpperBounds) {
                return;
            } else {
                pos.y += gravityAmount;
            }
        } else {
            pos.y += gravityAmount;
        }
    }

}

void Entity::updateSprite() {
    Sprite.pos = pos;
}


void Entity::initGravity(float newValue) {
    gravityAmount = newValue;
}

void Entity::changeSprite(std::string spriteLocation, SDL_Renderer * renderer) {
    const char * char_location = spriteLocation.c_str();
    Sprite.init(char_location, renderer, pos.x, pos.y, pos.w, pos.h);
}


void Entity::initGeneralCollision(float inXUpperBounds, float inXLowerBounds, float inYUpperBounds, float inYLowerBounds) {
    xUpperBounds = inXUpperBounds;
    xLowerBounds = inXLowerBounds;
    yUpperBounds = inYUpperBounds;
    yLowerBounds = inYLowerBounds;
}

void Entity::adjustHitbox(float inX, float inY, float inW, float  inH) {
    hitboxTweakX = inX;
    hitboxTweakY = inY;
    hitboxTweakW = inW;
    hitboxTweakH = inH;
}

void Entity::updateHitbox() {

    if (hitboxTweakX > 0) Hitbox.x = pos.x + hitboxTweakX; else {
        Hitbox.x = pos.x + hitboxTweakX;
    }
    if (hitboxTweakY > 0) Hitbox.y = pos.y + hitboxTweakY; else {
        Hitbox.y = pos.y + hitboxTweakY;
    }
    if (hitboxTweakW > 0) Hitbox.w = pos.w + hitboxTweakW; else {
        Hitbox.w = pos.w + hitboxTweakW;
    }
    if (hitboxTweakH > 0) Hitbox.h = pos.h + hitboxTweakH; else {
        Hitbox.h = pos.h + hitboxTweakH;
    }

}

void Entity::renderHitbox(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer, &Hitbox);
}

void Entity::initJump(float inJumpPower) {
    jumpPower = inJumpPower;
}

void Entity::jump() {
    jumpActive = true;
}

void Entity::updateJump() {

    if (jumpActive) {

        gravityEnabled = false;

        if (jumpTimer < 50) {
            jumpTimer++;
            pos.y -= jumpPower;
        } else {
            jumpActive = false;
            jumpTimer = 0;
            gravityEnabled = true;
        }

    }

}