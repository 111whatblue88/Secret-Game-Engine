#ifndef _ECS_HPP
#define _ECS_HPP

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
// text renderer
class TextRenderer{
  public:
  TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer);
  TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer, Transform transform);
  bool editText(std::string fontLocation, std::string text, int size, Color color);
  SDL_Texture* texture;
  int layer;
  bool inheritTransform;
  Transform transform;

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

class Entity {
private:
  std::string name;

  template<typename T>
  class Component {
  private:
    uint32_t m_componentCount = 0;
    std::unordered_map<uint32_t, T> m_components = {};
  public:
    // they told me templates were hell, i didnt believe them
    const std::unordered_map<uint32_t, T> getComponentList() {
      return m_components;
    }
    T& get(std::string name) {
      for (auto C : m_components) {
        if (C.second.GetName() == name) {
          return C.second; 
        }
      }
      return nullptr;
    }
    T& get(uint32_t ID) {
      return m_components[ID];
    }
    bool has() {
      if (m_components.empty()) {
        return false;
      } else {
        return true;
      }
    }
    void add(T component) {
      m_componentCount++;
      m_components.emplace(m_componentCount, component);
    }
    void remove(std::string name) {
      for (auto C : m_components) {
        if (C.second.GetName() == name) {
          m_components.erase(C.first);
        }
      }
    }
    void remove(uint32_t ID) {
      m_components.erase(ID);
    }

  };

public:
  bool SetName(std::string);
  std::string const GetName();
  
  Transform TransformComp;
  Component<ImgRenderer> ImgRendererComp;
  Component<PrimitiveRenderer> PrimitiveRendererComp;


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



