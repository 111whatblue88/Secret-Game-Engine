#ifndef _ECS_HPP
#define _ECS_HPP

#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../general/general.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include <sys/types.h>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace huge {
namespace ecs {

/*
// img renderer
class ImgRenderer{
  public:
  ImgRenderer(std::string location, SDL_FRect uv, int layer);
  ImgRenderer(std::string location, int layer);
  SDL_Texture* texture;
  SDL_FRect uv;
  int layer;
};

// PrimitiveRendering
class PrimitiveRenderer{
  public:
  enum class PrimitiveType {
    square, squareFill,
    circle, circleFill,
    line
  };
  PrimitiveType type;
  Color color;

  Vector2 LineTypeSecondPoint;

  PrimitiveRenderer(PrimitiveType type, Color color);
  PrimitiveRenderer(PrimitiveType type, Color color, Vector2 vec);
};
// physicsBody
class PhysicsBody{
  public:
  Vector2 velocity;
  bool isStatic;

  void addForce(Vector2 force);
  PhysicsBody();
};

// basicCollider
class BasicCollider{
  public:
  enum class Collidertype {
    boxCollider,
    circleCollider,
    lineCollider
  };
  Collidertype type;
  bool renderCollider;

  std::function<void()> onCollision;

  BasicCollider(Collidertype type);
  BasicCollider(Collidertype type, bool renderCollider);
  BasicCollider();
};

// Transform
class Transform {
  public:
  Transform(Vector2 pos, float width, float height);
  Transform(Vector2 pos, float radius);
  Transform();
  Vector2 pos;
  float height;
  float width;
  float radius;
  
  uint32_t getID();
  private:
  uint32_t ID;

};
*/ 


// PrimitiveRendering
class PrimitiveRenderer{
public:
  enum class PrimitiveType {
    square, squareFill,
    circle, circleFill,
    line
  };
  PrimitiveRenderer(PrimitiveType type, Color color);
  PrimitiveRenderer(PrimitiveType type, Color color, Vector2 vec);
  PrimitiveRenderer(std::string name, PrimitiveType type, Color color);
  PrimitiveRenderer(std::string name, PrimitiveType type, Color color, Vector2 vec);
  PrimitiveRenderer();
  PrimitiveType type;
  Color color;

  Vector2 LineTypeSecondPoint;

  std::string const GetName();
  bool SetName(std::string name);
private:
  std::string name;
};

// img renderer
class ImgRenderer{
public:
  ImgRenderer(std::string location, SDL_FRect uv, int layer);
  ImgRenderer(std::string location, int layer);
  ImgRenderer(std::string name, std::string location, SDL_FRect uv, int layer);
  ImgRenderer(std::string name,std::string location, int layer);
  ImgRenderer();
  SDL_Texture* texture;
  SDL_FRect uv;
  int layer;

  std::string const GetName();
  bool SetName(std::string name);
private:
  std::string name;
};

// Transform
class Transform {
public:
  Transform(Vector2 pos, float width, float height);
  Transform(Vector2 pos, float radius);
  Transform();
  Vector2 pos;
  float height;
  float width;
  float radius;

};

// text renderer
class TextRenderer{
public:
  TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer);
  TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer, Transform transform);
  TextRenderer(std::string name, std::string fontLocation, std::string text, int size, Color color, int layer);
  TextRenderer(std::string name, std::string fontLocation, std::string text, int size, Color color, int layer, Transform transform);
  TextRenderer();

  bool editFont(std::string fontLocation);
  bool editSize(int size);

  bool editText(std::string text);
  bool editColor(Color color);

  SDL_Texture* texture;
  int layer;
  bool inheritTransform;
  Transform transform;

  std::string const GetName();
  bool SetName(std::string name);
private:
  std::string name;

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

    const std::unordered_map<uint32_t, T>& getComponentList() {
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
      return m_components.at(1);
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
      return m_components.at(1);
    }


  };

public:
  bool SetName(std::string);
  std::string const GetName();
  
  Transform TransformComp;
  Component<ImgRenderer> ImgRendererComp;
  Component<PrimitiveRenderer> PrimitiveRendererComp;
  Component<TextRenderer> TextRendererComp;


  Entity();
  Entity(class Transform transform);
  Entity(std::string name, class Transform transform);

};

class EntitySys {
  public:

  static Entity& CreateEntity(Transform transform); 

  static bool update();

  static std::unordered_map<uint32_t, Entity>& GetEntityList();
  //static std::vector<uint32_t> getEntityComponentList();

  private:
  static std::unordered_map<uint32_t, Entity> m_entityList;
  static uint32_t m_entityCount;
  
};

}
}

#endif



