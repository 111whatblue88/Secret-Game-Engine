#ifndef _ENTITY_H
#define _ENTITY_H

#include "../include/ELOgine.hpp"

#include <string>
#include <SDL3/SDL.h>

class Health {
public:

    Health();
    int health;
    void init(float x, float y, float  w, float h, int setMaxHealth);
    SDL_FRect pos;
    void editHealth(int amount);
    void render(SDL_Renderer *renderer);
    
private:

    int maxHealth;
    SDL_FRect overBar;
    SDL_FRect underBar;

};

class Entity {
public:

    void initBase(float x, float y, float w, float h, float inSpeed);

    // normal stuff
    SDL_FRect pos;

    // collision
    // general collision is basic collision for something like the borders of the screen,
    // it gets checked when autoUpdateDir is called
    bool generalCollisionEnabled;
    void initGeneralCollision(float inXUpperBounds, float inXLowerBounds, float inYUpperBounds, float inYLowerBounds);
private:    
    float xUpperBounds, xLowerBounds, yUpperBounds, yLowerBounds;
public:
    SDL_FRect Hitbox;
    void adjustHitbox(float inX, float inY, float inW, float  inH);
private:
    float hitboxTweakX, hitboxTweakY, hitboxTweakW, hitboxTweakH;
public:
    void updateHitbox();
    void renderHitbox(SDL_Renderer *renderer);

    // inherited stuff, but not real inheritence cuz i dont mess with that
    Health EntityHealth;

    // sprite related stuff
    void updateSprite();
    void changeSprite(std::string spriteLocation, SDL_Renderer * renderer);
    Image Sprite;

    // gravity related
    bool gravityEnabled;
    void initGravity(float newValue);
private:
    float gravityAmount;
public:
    // jump related
    // note: enabling jumping removes being able to move vertically freely
    bool jumpEnabled;
    void initJump(float inJumpPower);
    void jump();
    void updateJump();
    bool jumpActive;
private:
    int jumpTimer;
    float jumpPower;
public:

    // direction stuff
    enum class dir {
        up, down, left, right, none
    };

    dir currentDir;    
    float speed;
    void autoUpdateDir();
    void updateDir(dir inDir);
    void move();

};

#endif