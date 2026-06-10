#include "ecs.hpp"
#include "../secret.hpp"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_oldnames.h>
#include <cmath>
#include <SDL3/SDL_gpu.h>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <sys/types.h>

using namespace secret;
using namespace ecs;
using namespace rend;
using namespace audio;

using ID = uint32_t;

// Transform
Transform::Transform(Vec2 pos){
  this->pos=pos;
}
Transform::Transform() {
  this->pos={0,0};
}

// Component
std::string const Component::GetName() {
  return m_name;
}
bool Component::SetName(std::string name) {
  this->m_name=name;
  return true;
}

// IMG Renderer 
ImgRenderer::ImgRenderer(std::string location, SDL_FRect uv, int layer) {
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
};
ImgRenderer::ImgRenderer(std::string location, int layer) {
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv={0,0,0,0};
};
ImgRenderer::ImgRenderer(std::string name, std::string location, SDL_FRect uv, int layer) {
  this->SetName(name);
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
}
ImgRenderer::ImgRenderer(std::string name, std::string location, int layer) {
  this->SetName(name);
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv={0,0,0,0};
}
ImgRenderer::ImgRenderer() {
  this->texture=NULL;
  this->layer=0;
  this->uv={0,0,0,0};
}

// Primitive Renderer 
PrimitiveRenderer::PrimitiveRenderer(Color color, Vec2 p1, Vec2 p2) {
this->SetName("defaultName");
this->type = PrimitiveType::line;
this->fill = false;
this->color = color;
this->rect = {{0,0},0,0};
this->circle = {{0,0},0};
this->firstLinePoint = p1;
this->secondLinePoint = p2;
}
PrimitiveRenderer::PrimitiveRenderer(std::string name, Color color, Vec2 p1, Vec2 p2) {
this->SetName(name);
this->type = PrimitiveType::line;
this->fill = false;
this->color = color;
this->rect = {{0,0},0,0};
this->circle = {{0,0},0};
this->firstLinePoint = p1;
this->secondLinePoint = p2;
}

PrimitiveRenderer::PrimitiveRenderer(Color color, bool fill, Rect rect) {
this->SetName("defaultName");
this->type = PrimitiveType::square;
this->fill = fill;
this->color = color;
this->rect = rect;
this->circle = {{0,0},0};
this->firstLinePoint = {0,0};
this->secondLinePoint = {0,0};
}
PrimitiveRenderer::PrimitiveRenderer(std::string name, Color color, bool fill, Rect rect) {
this->SetName(name);
this->type = PrimitiveType::square;
this->fill = fill;
this->color = color;
this->rect = rect;
this->circle = {{0,0},0};
this->firstLinePoint = {0,0};
this->secondLinePoint = {0,0};
}

PrimitiveRenderer::PrimitiveRenderer(std::string name, Color color, bool fill, Circle circle) {
this->SetName(name);
this->type = PrimitiveType::circle;
this->fill = fill;
this->color = color;
this->rect = {{0,0},0,0};
this->circle = circle;
this->firstLinePoint = {0,0};
this->secondLinePoint = {0,0};
}
PrimitiveRenderer::PrimitiveRenderer(Color color, bool fill, Circle circle) {
this->SetName("defaultName");
this->type = PrimitiveType::circle;
this->fill = fill;
this->color = color;
this->rect = {{0,0},0,0};
this->circle = circle;
this->firstLinePoint = {0,0};
this->secondLinePoint = {0,0};
}

PrimitiveRenderer::PrimitiveRenderer() {
this->SetName("defaultName");
this->type = PrimitiveType::line;
this->fill = false;
this->color = {0,0,0};
this->rect = {{0,0},0,0};
this->circle = {{0,0},0};
this->firstLinePoint = {0,0};
this->secondLinePoint = {0,0};
}

// Text Renderer
TextRenderer::TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer) {
  this->SetName("defaultName");
  this->fontLocation=fontLocation;
  this->text=text;
  this->size=size;
  this->color=color;
  this->layer=layer;

  this->font = rend::RenderSys::m_renderer.createFont(fontLocation, size);
  this->texture=rend::RenderSys::m_renderer.textureFromFont(font ,color,text);
}
TextRenderer::TextRenderer(std::string name, std::string fontLocation, std::string text, int size, Color color, int layer) {
  this->SetName(name);
  this->fontLocation=fontLocation;
  this->text=text;
  this->size=size;
  this->color=color;
  this->layer=layer;

  this->font = rend::RenderSys::m_renderer.createFont(fontLocation, size);
  this->texture=rend::RenderSys::m_renderer.textureFromFont(font,color,text);
}

TextRenderer::TextRenderer() {
  this->SetName("defaultName");
  this->fontLocation="";
  this->text="";
  this->size=0;
  this->color={0, 0,0};
  this->layer=0;

  this->font = rend::RenderSys::m_renderer.createFont(fontLocation, size);

  this->texture=nullptr;
}

bool TextRenderer::editFont(std::string fontLocation) {
  this->fontLocation = fontLocation;
  this->texture = rend::RenderSys::m_renderer.textureFromFont(fontLocation, size, color, text);
  if (!texture) {
    return false;
  } else {
    return true;
  }
}
bool TextRenderer::editSize(int size) {
  this->size=size;
  this->texture = rend::RenderSys::m_renderer.textureFromFont(fontLocation, size, color, text);
  if (!texture) {
    return false;
  } else {
    return true;
  }
}
bool TextRenderer::editText(std::string text) {
  this->text=text;
  this->texture = rend::RenderSys::m_renderer.textureFromFont(font, color, text);
  if (!texture) {
    return false;
  } else {
    return true;
  }
}
bool TextRenderer::editColor(Color color) {
  this->color=color;
  this->texture = rend::RenderSys::m_renderer.textureFromFont(font, color, text);
  if (!texture) {
    return false;
  } else {
    return true;
  }
}


bool AudioEmitter::playAudio() {
  if (AudioSys::PlayAudio(stream->stream)) {
    return true;
  } else {
    return false;
  }
}
bool AudioEmitter::pauseAudio() {
  if (AudioSys::PauseAudio(stream->stream)) {
    return true;
  } else {
    return false;
  }
}

AudioEmitter::~AudioEmitter() {
  SDL_DestroyAudioStream(stream->stream);
  SDL_free(stream->audioData);
  free(stream);
}
AudioEmitter::AudioEmitter() {
  SetName("defaultName");
  this->stream = new audio::AudioSys::audioStream();
}
AudioEmitter::AudioEmitter(std::string WAVLocation) {
  SetName("defaultName");
  this->stream=audio::AudioSys::audioStreamFromWAV(WAVLocation);  
}
AudioEmitter::AudioEmitter(std::string name, std::string WAVLocation) {
  SetName(name);
  this->stream=audio::AudioSys::audioStreamFromWAV(WAVLocation);  
}
  

// Physics Body
PhysicsBody::PhysicsBody() {
  isStatic = true;
  gravityEnabled = false;
  velocity = {0,0};
  angularVelocity = 0;
  mass = 1;
}
void PhysicsBody::applyImpulse(Vec2 impulse) {
  this->velocity = this->velocity + impulse.scale(1/ this->mass);
}


// Collider 
BasicBoxCollider::BasicBoxCollider(Rect colliderRect) {
  this->SetName("defaultName");
  this->colliderBox = colliderRect;
  this->renderCollider = false;
  this->onCollision = [&](){};
}
BasicBoxCollider::BasicBoxCollider(std::string name, Rect colliderRect) {
  this->SetName(name);
  this->colliderBox = colliderRect;
  this->renderCollider = false;
  this->onCollision = [&](){};
}
BasicBoxCollider::BasicBoxCollider(std::string name) {
  this->SetName(name);
  this->colliderBox = {Vec2{0,0},0,0};
  this->renderCollider = false;
  this->onCollision = [&](){};
}
BasicBoxCollider::BasicBoxCollider() {
  this->SetName("defaultName");
  this->colliderBox = {Vec2{0,0},0,0};
  this->renderCollider = false;
  this->onCollision = [&](){};
}

BasicBoxCollider::Collision BasicBoxCollider::isColliding(Rect a, Rect b) {

  Collision result{};

  float aLeft   = a.pos.x;
  float aRight  = a.pos.x + a.width;
  float aTop    = a.pos.y;
  float aBottom = a.pos.y + a.height;

  float bLeft   = b.pos.x;
  float bRight  = b.pos.x + b.width;
  float bTop    = b.pos.y;
  float bBottom = b.pos.y + b.height;

  float overlapLeft   = aRight - bLeft;
  float overlapRight  = bRight - aLeft;
  float overlapTop    = aBottom - bTop;
  float overlapBottom = bBottom - aTop;

  if (overlapLeft <= 0 ||
      overlapRight <= 0 ||
      overlapTop <= 0 ||
      overlapBottom <= 0)
  {
      return result;
  }

  result.hit = true;

  float minOverlapX =
      (overlapLeft < overlapRight)
      ? overlapLeft
      : -overlapRight;

  float minOverlapY =
      (overlapTop < overlapBottom)
      ? overlapTop
      : -overlapBottom;

  if (abs(minOverlapX) < abs(minOverlapY)){
    result.depth = abs(minOverlapX);
    result.normal = {
        minOverlapX < 0 ? -1.0f : 1.0f,
        0.0f
    };
  }
  else{
    result.depth = abs(minOverlapY);
    result.normal = {
        0.0f,
        minOverlapY < 0 ? -1.0f : 1.0f
    };
  }

  return result;
};

PlayerController::PlayerController() {
  enabled = false;
}


// Entity struct
bool Entity::SetName(std::string name) {
  this->name=name;
  return true;
}
std::string const Entity::GetName() {
  return name;
}
Entity::Entity() {
  this->name = "defaultName";
  this->TransformComp.pos = {0,0};
}
Entity::Entity(class Transform transform) {
  this->name = "defaultName";
  this->TransformComp = transform;
}
Entity::Entity(std::string name, class Transform transform) {
  this->name = name;
  this->TransformComp = transform;
}

// EntitySys
std::unordered_map<uint32_t, Entity> EntitySys::m_entityList = {};
uint32_t EntitySys::m_entityCount = 0;
Entity& EntitySys::CreateEntity(Transform transform) {
  m_entityCount++;
  m_entityList.emplace(m_entityCount, Entity(transform));
  return m_entityList[m_entityCount];
}
std::unordered_map<uint32_t, Entity>& EntitySys::GetEntityList() {
  return m_entityList;
}
bool EntitySys::update() {
  
  auto& EList = EntitySys::GetEntityList();

  for (auto& E : EList) {

    // img renderer
    if (E.second.ImgRendererComp.has()) {
      for (auto& IR : E.second.ImgRendererComp.getComponentList()) {

        if (IR.second.uv.x || IR.second.uv.y || IR.second.uv.w || IR.second.uv.h) {
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RTEXTURE,
            RenderSys::PositionalData{(E.second.TransformComp.pos + IR.second.location.pos)},
            RenderSys::SizeData{IR.second.location.width, IR.second.location.height},
            RenderSys::RenderingData{Color(0,0,0),IR.second.texture, IR.second.uv,0}
          });
        } else {
          if (!IR.second.texture) {
          }
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RFULLTEXTURE,
            RenderSys::PositionalData{(E.second.TransformComp.pos + IR.second.location.pos)},
            RenderSys::SizeData{IR.second.location.width, IR.second.location.height},
            RenderSys::RenderingData{Color(0,0,0),IR.second.texture, 0,0,0,0,0}
          });
        }
      }
    }

    // primitve renderer
    if (E.second.PrimitiveRendererComp.has()) {
      for (auto& PR : E.second.PrimitiveRendererComp.getComponentList()) {
        switch (PR.second.type) {
          case ecs::PrimitiveRenderer::PrimitiveType::square: {
            if (PR.second.fill) {
              RenderSys::CallList.push_back(RenderSys::RenderCall{
                RenderSys::CallType::RBOXFILL,
                RenderSys::PositionalData{E.second.TransformComp.pos+PR.second.rect.pos},
                RenderSys::SizeData{PR.second.rect.width, PR.second.rect.height},
                RenderSys::RenderingData{PR.second.color}
              });
            } else {
              RenderSys::CallList.push_back(RenderSys::RenderCall{
                RenderSys::CallType::RBOX,
                RenderSys::PositionalData{E.second.TransformComp.pos+PR.second.rect.pos},
                RenderSys::SizeData{PR.second.rect.width, PR.second.rect.height},
                RenderSys::RenderingData{PR.second.color}
              });
            }
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::circle: {
            if (PR.second.fill) {
              RenderSys::CallList.push_back(RenderSys::RenderCall{
                RenderSys::CallType::RCIRCLEFILL,
                RenderSys::PositionalData{E.second.TransformComp.pos+PR.second.circle.pos},
                RenderSys::SizeData{0,0,PR.second.circle.radius},
                RenderSys::RenderingData{PR.second.color}
              });
            } else {
              RenderSys::CallList.push_back(RenderSys::RenderCall{
                RenderSys::CallType::RCIRCLE,
                RenderSys::PositionalData{E.second.TransformComp.pos+PR.second.circle.pos},
                RenderSys::SizeData{0,0,PR.second.circle.radius},
                RenderSys::RenderingData{PR.second.color}
              });
            }
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::line: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RLINE,
              RenderSys::PositionalData{PR.second.firstLinePoint, PR.second.secondLinePoint},
              RenderSys::SizeData{},
              RenderSys::RenderingData{PR.second.color}
            });
            break;
          }
        }
      }      
    }

    // Text Renderer
    if (E.second.TextRendererComp.has()) {
      for (auto& TR : E.second.TextRendererComp.getComponentList()) {
        RenderSys::CallList.push_back(RenderSys::RenderCall{
          RenderSys::CallType::RFULLTEXTURE,
          RenderSys::PositionalData{(E.second.TransformComp.pos + TR.second.location.pos)},
          RenderSys::SizeData{TR.second.location.width, TR.second.location.height},
          RenderSys::RenderingData{{0,0,0}, TR.second.texture}
        });
      }
    }

    if (E.second.BasicBoxColliderComp.has()) {
      for (auto& BC : E.second.BasicBoxColliderComp.getComponentList()) {
        if (BC.second.renderCollider) {
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RBOX,
            RenderSys::PositionalData{(E.second.TransformComp.pos + BC.second.colliderBox.pos)},
            RenderSys::SizeData{BC.second.colliderBox.width, BC.second.colliderBox.height},
            RenderSys::RenderingData{Color(255,0,0)}
          });
        }
      }
    }

    // PhysicsBody

    Vec2 GRAVITY = {0,9.81};

    if (!E.second.PhysicsBodyComp.isStatic) {
      if (E.second.PhysicsBodyComp.gravityEnabled) {
        E.second.PhysicsBodyComp.velocity = E.second.PhysicsBodyComp.velocity + GRAVITY.scale(core::Engine::deltaTime());
      }
      E.second.TransformComp.pos = E.second.TransformComp.pos + E.second.PhysicsBodyComp.velocity.scale(core::Engine::deltaTime());
    }

    if (E.second.BasicBoxColliderComp.has()) {
      for (auto& BC : E.second.BasicBoxColliderComp.getComponentList()) {
        for (auto& other : EList) {

          if (E.first == other.first) {
            continue;
          }
          for (auto& otherBC : other.second.BasicBoxColliderComp.getComponentList()) {

            Rect thisRect = {(E.second.TransformComp.pos+BC.second.colliderBox.pos), BC.second.colliderBox.width, BC.second.colliderBox.height};
            Rect otherRect = {(other.second.TransformComp.pos+otherBC.second.colliderBox.pos), otherBC.second.colliderBox.width, otherBC.second.colliderBox.height};

            BasicBoxCollider::Collision collision = BasicBoxCollider::isColliding(thisRect, otherRect);
            if (collision.hit) {

              if (E.second.PhysicsBodyComp.isStatic) {
                continue;
              }

              if (!other.second.PhysicsBodyComp.isStatic) {
                float correction = collision.depth * 0.5f;

                E.second.TransformComp.pos.x -= collision.normal.x * correction;
                E.second.TransformComp.pos.y -= collision.normal.y * correction;

                other.second.TransformComp.pos.x += collision.normal.x * correction;
                other.second.TransformComp.pos.y += collision.normal.y * correction;
              } else {
                E.second.TransformComp.pos.x -= collision.normal.x * collision.depth;
                E.second.TransformComp.pos.y -= collision.normal.y * collision.depth;

              }

              if (collision.normal.x != 0) { 
                if (E.second.PlayerControllerComp.enabled) {
                  E.second.PhysicsBodyComp.velocity.x = 0;
                } else {
                E.second.PhysicsBodyComp.velocity.x = -(E.second.PhysicsBodyComp.velocity.x);
                }
              }

              if (collision.normal.y != 0) {
                if (E.second.PlayerControllerComp.enabled) {
                  E.second.PhysicsBodyComp.velocity.y = 0;
                } else {
                E.second.PhysicsBodyComp.velocity.y = -(E.second.PhysicsBodyComp.velocity.y);
                }
              }

              BC.second.onCollision();
              otherBC.second.onCollision();

              } else {
                continue;
              }



          }
        }
      }
    }




























  }
  return true;
};



