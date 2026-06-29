#ifndef _ECS_HPP
#define _ECS_HPP

#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../general/general.hpp"
#include "../audio/audio.hpp"

#include <SDL3/SDL_audio.h>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <functional>
#include <numeric>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace secret {
namespace ecs {

class Entity;

// Transform
class Transform {
public:
  Transform(Vec2 pos);
  Transform();

  Vec2 pos;

};

// base Component class 
class Component {
public:

  std::string const GetName();
  bool SetName(std::string name);

private:
  std::string m_name;
};

// physicsBody
class PhysicsBody {
public:
  PhysicsBody();

  bool isStatic;
  bool gravityEnabled;

  float mass;

  Vec2 velocity;
  float angularVelocity;

  void applyImpulse(Vec2 impulse);

private:

};

class PlayerController{
  public:
  PlayerController();
  bool enabled;
};

// basicBoxCollider
class BasicBoxCollider : public Component{
  public:

  struct Collision {
    bool hit;
    Vec2 normal;
    float depth;
  };

  Rect colliderBox;

  bool renderCollider;

  std::function<void()> onCollision;

  static Collision isColliding(Rect e, Rect other);

  BasicBoxCollider(Rect colliderRect);
  BasicBoxCollider(std::string name);
  BasicBoxCollider(std::string name, Rect colliderRect);
  BasicBoxCollider();
};

// PrimitiveRendering
class PrimitiveRenderer : public Component{
public:
  enum class PrimitiveType {
    square,
    circle,
    line
  };

  PrimitiveRenderer();

  PrimitiveRenderer(Color color, Vec2 p1, Vec2 p2);
  PrimitiveRenderer(std::string name, Color color, Vec2 p1, Vec2 p2);

  PrimitiveRenderer(Color color, bool fill, Rect rect);
  PrimitiveRenderer(std::string name, Color color, bool fill, Rect rect);

  PrimitiveRenderer(Color color, bool fill, Circle circle);
  PrimitiveRenderer(std::string name, Color color, bool fill, Circle circle);
 
  bool fill;

  PrimitiveType type;
  Color color;
 
  Rect rect;
  Circle circle;

  Vec2 firstLinePoint;
  Vec2 secondLinePoint;

};

// img renderer
class ImgRenderer : public Component{
public:
  ImgRenderer(std::string location, SDL_FRect uv, int layer);
  ImgRenderer(std::string location, int layer);
  ImgRenderer(std::string name, std::string location, SDL_FRect uv, int layer);
  ImgRenderer(std::string name, std::string location, int layer);
  ImgRenderer();

  Rect location;

  SDL_Texture* texture;
  SDL_FRect uv;
  int layer;
};

// audioEmitter
class AudioEmitter : public Component{
public:
  
  AudioEmitter();
  AudioEmitter(std::string soundFileLocation);
  AudioEmitter(std::string name, std::string audioFileLocation);

  bool loadFile(std::string audioFileLocation);

  bool playAudio();
  bool resumeAudio();
  bool pauseAudio();
  bool restartAudio();

private:

  MIX_Track* track;

};

// text renderer
class TextRenderer : public Component{
public:
  TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer);
  TextRenderer(std::string name, std::string fontLocation, std::string text, int size, Color color, int layer);
  TextRenderer();

  Rect location;

  bool editFont(std::string fontLocation);
  bool editSize(int size);

  bool editText(std::string text);
  bool editColor(Color color);

  SDL_Texture* texture;
  int layer;

private:

  std::string text;
  TTF_Font* font;
  Color color;
  int size;
  std::string fontLocation;

};

class Entity {
private:
  std::string name;

  template<typename T>
  class Component {
  private:
    uint32_t m_componentCount = 0;
    std::unordered_map<uint32_t, T> m_components = {};
  public:

    std::unordered_map<uint32_t, T>& getComponentList() {
      return m_components;
    }

    void add(T component) {
      m_componentCount++;
      m_components.emplace(m_componentCount, component);
    }
    template<typename... Args>
    void add(T component, Args... args) {
      add(component);
      add(args...);
    }

    void remove(const std::string& name) {
      for (auto it = m_components.begin(); it != m_components.end();) {
        if (it->second.GetName() == name) {
          it = m_components.erase(it);
        } else {
          ++it;
        }
      }
    }
    void remove(const uint32_t& ID) {
      for (auto it = m_components.begin(); it != m_components.end();) {
        if (it->first == ID) {
          it = m_components.erase(it);
        } else {
          ++it;
        }
      }
    }

    bool has() {
      if (m_components.empty()) {
        return false;
      } else {
        return true;
      }
    }

    T& get(const uint32_t& ID) {
      return m_components.at(ID);
    }
    T& get(const std::string& name) {
      for (auto it = m_components.begin(); it != m_components.end();it++) {
        if (it->second.GetName() == name) {
          return get(it->first);
        }
      }
      // this does NOTHING its just to suppress a warning. Do NOT call this function with an 
      // invalid component name
      return m_components.at(0);
    }

    T& operator[](const uint32_t& ID) {
      return m_components.at(ID);
    }
    T& operator[](const std::string& name) {
      for (auto it = m_components.begin(); it != m_components.end();it++) {
        if (it->second.GetName() == name) {
          return get(it->first);
        }
      }
      // this does NOTHING its just to suppress a warning. Do NOT call this function with an 
      // invalid component name
      return m_components.at(0);
    }


  };

public:
  bool SetName(std::string);
  std::string const GetName();
  
  Transform TransformComp;
  PhysicsBody PhysicsBodyComp;
  PlayerController PlayerControllerComp;

  Component<ImgRenderer> ImgRendererComp;
  Component<PrimitiveRenderer> PrimitiveRendererComp;
  Component<TextRenderer> TextRendererComp;
  Component<BasicBoxCollider> BasicBoxColliderComp;
  Component<AudioEmitter> AudioEmitterComp;

  Entity();
  Entity(class Transform transform);
  Entity(std::string name, class Transform transform);

};

class EntitySys {
  public:

  static Entity& CreateEntity(Transform transform); 
  static Entity& CreateEntity(std::string name, Transform transform); 

  static bool update();

  static std::unordered_map<uint32_t, Entity>& GetEntityList();
  static std::vector<uint32_t> getEntityComponentList();

  static Entity& findEntity(std::string name);

  private:
  static std::unordered_map<uint32_t, Entity> m_entityList;
  static uint32_t m_entityCount;
  
};

}
}

#endif



