#ifndef _ECS_HPP
#define _ECS_HPP

#include "../general/general.hpp"

#include <algorithm>
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

template <typename T>
class ComponentList {
  private:
  std::unordered_map<uint32_t, T> validComponents = {};
  uint32_t count = 0; 
  public:

  T& add(uint32_t e, T component) {
    count++;
    validComponents.emplace(e, component);
    return validComponents.at(e);
  }

  T& get(uint32_t e) {
    return validComponents[e];
  }
  void remove(uint32_t entity, uint32_t component) {
    validComponents[entity].erase(component);
  }
  bool has(uint32_t e) {
    if (validComponents.count(e)) {
      return true;
    } 
    return false;
  }

  std::unordered_map<uint32_t, T>& getComponentList() {
    return validComponents;
  }
  uint32_t getComponentCount() {
    return count;
  }


};

class EntitySys {
  public:

  static uint32_t createEntity(Transform transform); 
  template <typename T>
  static T& addComponent(uint32_t e, T component);

  static bool updateComponents();

  static ComponentList<Transform> TransformComp;
  static ComponentList<TextRenderer> TextRendererComp;
  static ComponentList<PrimitiveRenderer> PrimitiveRendererComp;
  static ComponentList<ImgRenderer> ImgRendererComp;
  static ComponentList<BasicCollider> BasicColliderComp;
  static ComponentList<PhysicsBody> PhysicsBodyComp;

  static std::vector<uint32_t> getEntityList();
  //static std::vector<uint32_t> getEntityComponentList();

  private:
  static std::vector<uint32_t> validEntities;
  static uint32_t m_entityCount;
  
};

}
}

#endif



