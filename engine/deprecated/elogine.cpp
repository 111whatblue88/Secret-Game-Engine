#include "elogine.hpp"
#include "ecs/ecs.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <string>
#include <format>
#include <algorithm>

namespace engine {
namespace core {

  Elogine::Elogine(std::string windowName, int width, int height) 
    :m_WINDOWWIDTH(width), m_WINDOWHEIGHT(height), renderSys(windowName, width, height), running(true), entitySys(40) {
    if (!SDL_WasInit(SDL_INIT_VIDEO)) {
      if (SDL_Init(SDL_INIT_VIDEO)) {
        elogine::terminal::Output::log(
            elogine::terminal::Output::colorString(
              "SDL init error", 
              elogine::terminal::Output::Color::green
            ),
            elogine::terminal::Output::LogLevel::normal
        );
      } 
    }
    if (TTF_WasInit() == 0) {
      if (!TTF_Init()) {
        elogine::terminal::Output::log(
            elogine::terminal::Output::colorString(
              "TTF init error", 
              elogine::terminal::Output::Color::green
            ),
            elogine::terminal::Output::LogLevel::normal
        );
      }
    }

  }

  Elogine::~Elogine() {
    SDL_Quit();
    TTF_Quit();
    elogine::terminal::Output::log(
        elogine::terminal::Output::colorString(
          "elogine exiting", 
          elogine::terminal::Output::Color::green
        ),
        elogine::terminal::Output::LogLevel::normal
    );
  }

  bool Elogine::run() {


    elogine::terminal::Output::log(
        elogine::terminal::Output::colorString(
          "elogine started", 
          elogine::terminal::Output::Color::green
        ),
        elogine::terminal::Output::LogLevel::normal
    );

    SDL_Event testevent;

    uint64_t lastFrametime = SDL_GetTicks();

    //main loop
    while (!inputSys.quit) {

      uint64_t currentFrametime = SDL_GetTicks();
      m_deltaTime = (currentFrametime-lastFrametime)/1000.0f;
      lastFrametime = currentFrametime; 

      inputSys.Input();

      update();

      renderSys.render(*this);


      uint32_t frametime = SDL_GetTicks() - currentFrametime;
      if (frametime<1000/ engineOptions.m_targetFPS) {
        SDL_Delay((1000/engineOptions.m_targetFPS)-frametime);
      }

    } 

    return true;
  }

  void Elogine::earlyExit() {
    running = false;
    elogine::terminal::Output::log(
        elogine::terminal::Output::colorString(
          "exiting early...", 
          elogine::terminal::Output::Color::white 
        ),
        elogine::terminal::Output::LogLevel::normal
    );
  }

  float Elogine::deltaTime() {return m_deltaTime;}

  bool Elogine::update() {

    for (size_t i = 0; i < entitySys.validEntities.size(); i++) {
        if (entitySys.rigidBodyComponent.has(entitySys.validEntities[i])) {
          ecs::RigidBody& rb = entitySys.rigidBodyComponent.get(entitySys.validEntities[i]);
          ecs::Transform& t = entitySys.transformComponent.get(entitySys.validEntities[i]);

          if (rb.gravityEnabled) {
            rb.acc.y += 20 * deltaTime();
          }

          rb.vel.x += rb.acc.x * deltaTime();
          rb.vel.y += rb.acc.y * deltaTime();

          rb.vel.x = rb.vel.x*0.9;
          rb.vel.y = rb.vel.y*0.9;

          if (rb.vel.x > entitySys.rigidBodyComponent.entityMaxSpeed) {
            rb.vel.x = entitySys.rigidBodyComponent.entityMaxSpeed;
          }
          if (rb.vel.y > entitySys.rigidBodyComponent.entityMaxSpeed) {
            rb.vel.y = entitySys.rigidBodyComponent.entityMaxSpeed;
          }

          t.position.x += rb.vel.x;
          t.position.y += rb.vel.y;


        }
    }    
    for (size_t i = 0; i < entitySys.validEntities.size(); i++) {
      if (entitySys.colliderComponent.has(entitySys.validEntities[i])) {
        ecs::Collider objCol1 = entitySys.colliderComponent.get(entitySys.validEntities[i]);
        ecs::Transform objTra1 = entitySys.transformComponent.get(entitySys.validEntities[i]);
        for (size_t t = 0; t < entitySys.validEntities.size(); t++) {
          if ( i == t) {continue;}
          if (entitySys.colliderComponent.has(entitySys.validEntities[t])) {
            ecs::Collider objCol2 = entitySys.colliderComponent.get(entitySys.validEntities[t]);
            ecs::Transform objTra2 = entitySys.transformComponent.get(entitySys.validEntities[t]);
            if(objTra1.position.x < objTra2.position.x + objTra2.width &&
                objTra1.position.x + objTra1.width > objTra2.position.x &&
                objTra1.position.y < objTra2.position.y + objTra2.height &&
                objTra1.position.y + objTra1.height > objTra2.position.y
            ) {

              if (objCol1.isTrigger) {
                objCol1.onTrigger();
                continue;
              }
              if (objCol2.isTrigger) {
                objCol2.onTrigger();
                continue;
              }
              if (entitySys.rigidBodyComponent.has(entitySys.validEntities[i])) {
                ecs::RigidBody& objRig1 =  entitySys.rigidBodyComponent.get(entitySys.validEntities[i]);

                if (entitySys.playerCtrlComponent.has(entitySys.validEntities[i])) {
                  if (objTra1.position.x+objTra1.width >= objTra2.position.x &&
                  objTra1.position.x < objTra2.position.x){
                    if (!(objRig1.vel.x <= 0)) {
                      objRig1.addForce(ecs::Vector2(-(objRig1.vel.x), 0));
                    }
                  }
                  if (objTra1.position.x <= objTra2.position.x+objTra2.width && 
                  objTra2.position.x < objTra1.position.x){
                    if (!(objRig1.vel.x >= 0)) {
                      objRig1.addForce(ecs::Vector2(-(objRig1.vel.x), 0));
                    }
                  }
                  if (objTra1.position.y+objTra1.height >= objTra2.position.y &&
                  objTra2.position.y+objTra2.height > objTra1.position.y) {
                    if (!(objRig1.vel.y <= 0)) {
                      objRig1.addForce(ecs::Vector2(0, -(objRig1.vel.y)));
                    }
                  }
                  if (objTra1.position.y <= objTra2.position.y+objTra2.height &&
                  objTra2.position.y < objTra1.position.y+objTra1.height){
                    if (!(objRig1.vel.y >= 0)) {
                      objRig1.addForce(ecs::Vector2(0, -(objRig1.vel.y)));
                    }
                  }
                } else {
                  if (objTra1.position.x+objTra1.width >= objTra2.position.x &&
                  objTra1.position.x < objTra2.position.x){
                    if (!(objRig1.vel.x <= 0)) {
                      objRig1.addForce(ecs::Vector2(-(objRig1.vel.x)*2, 0));
                    }
                  }
                  if (objTra1.position.x <= objTra2.position.x+objTra2.width && 
                  objTra2.position.x < objTra1.position.x){
                    if (!(objRig1.vel.x >= 0)) {
                      objRig1.addForce(ecs::Vector2(-(objRig1.vel.x)*2, 0));
                    }
                  }
                  if (objTra1.position.y+objTra1.height >= objTra2.position.y &&
                  objTra2.position.y+objTra2.height > objTra1.position.y) {
                    if (!(objRig1.vel.y <= 0)) {
                      objRig1.addForce(ecs::Vector2(0, -(objRig1.vel.y)*2));
                    }
                  }
                  if (objTra1.position.y <= objTra2.position.y+objTra2.height &&
                  objTra2.position.y < objTra1.position.y+objTra1.height){
                    if (!(objRig1.vel.y >= 0)) {
                      objRig1.addForce(ecs::Vector2(0, -(objRig1.vel.y)*2));
                    }
                  }
                }
              }
            }
          }
        }
      }
    }    

    Update();

    return true;
  }


  Elogine::Options::Options() {
    m_targetFPS=60;

  }  


} //namespace core
} // namespace elogine
