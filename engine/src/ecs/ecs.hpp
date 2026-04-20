#ifndef _ECS_HPP
#define _ECS_HPP

#include "../general/general.hpp"

#include <functional>
#include <string>
#include <SDL3/SDL.h>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace elo {
namespace ecs {

// attempting templates - not usable

template <typename T> class component {

};

uint32_t createEntity();



// Transform
class Transform {
  public:
  Transform(Vector2 pos, float width, float height);
  Transform(Vector2 pos, float radius);
  Vector2 pos;
  float height;
  float width;
  float radius;
};
class TransformComponent {
  public:
  static void add(uint32_t entity, Transform transform);
  static Transform& get(uint32_t entity); 
  static const bool has(uint32_t entity);

  private:
  static std::unordered_map<uint32_t, Transform> entityList; 
};

// img renderer
class ImgRenderer{
  public:
  ImgRenderer(std::string location, SDL_FRect uv, int layer);
  ImgRenderer(std::string location, int layer);
  SDL_Texture* texture;
  SDL_FRect uv;
  int layer;
};
class ImgRendererComp{
  public:
  static void add(uint32_t entity, ImgRenderer ir);
  static void rem(uint32_t entity);
  static ImgRenderer& get(uint32_t entity); 
  static const bool has(uint32_t entity);

  static std::unordered_map<uint32_t, ImgRenderer> getEntityList();

  private:
  static std::unordered_map<uint32_t, ImgRenderer> entityList; 
};

// text renderer
class TextRenderer{
  public:
  TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer);
  bool editText(std::string fontLocation, std::string text, int size, Color color);
  SDL_Texture* texture;
  int layer;
};
class TextRendererComp{
  public:
  static void add(uint32_t entity, TextRenderer tr);
  static void rem(uint32_t entity);
  static TextRenderer& get(uint32_t entity); 
  static const bool has(uint32_t entity);

  static std::unordered_map<uint32_t, TextRenderer> getEntityList();

  private:
  static std::unordered_map<uint32_t, TextRenderer> entityList; 
};

// PrimitiveRendering
class PrimitiveRenderer{
  public:
  enum class PrimitiveType {
    square, sqaureFill,
    circle, circleFill
  };
  PrimitiveType type;
  Color color;

  PrimitiveRenderer(PrimitiveType type, Color color);
};
class PrimitiveRendererComponent{
  public:
  static void add(uint32_t entity, PrimitiveRenderer pr);
  static void rem(uint32_t entity);
  static PrimitiveRenderer& get(uint32_t entity); 
  static const bool has(uint32_t entity);

  static std::unordered_map<uint32_t, PrimitiveRenderer> getEntityList();

  private:
  static std::unordered_map<uint32_t, PrimitiveRenderer> entityList; 
};

// physicsBody
class PhysicsBody{
  public:
  Vector2 velocity;

  void addForce(Vector2 force);
};
class PhysicsBodyComponent{
  public:
  static void add(uint32_t entity, PhysicsBody bc);
  static void rem(uint32_t entity);
  static PhysicsBody& get(uint32_t entity); 
  static const bool has(uint32_t entity);

  static std::unordered_map<uint32_t, PhysicsBody> getEntityList();

  private:
  static std::unordered_map<uint32_t, PhysicsBody> entityList; 
};

// basicCollider
class BasicCollider{
  public:
  enum class Collidertype {
    boxCollider,
    circleCollider
  };
  Collidertype type;
  bool renderCollider;

  std::function<void()> onCollision;

  BasicCollider(Collidertype type, bool renderCollider);
};
class BasicColliderComponent{
  public:
  static void add(uint32_t entity, BasicCollider bc);
  static void rem(uint32_t entity);
  static BasicCollider& get(uint32_t entity); 
  static const bool has(uint32_t entity);

  static std::unordered_map<uint32_t, BasicCollider> getEntityList();

  static bool isColliding(uint32_t e1, uint32_t e2);

  private:
  static std::unordered_map<uint32_t, BasicCollider> entityList; 
};

class EntitySys {
  public:

  static uint32_t addEntity(Transform init);
  static void remEntity(uint32_t ID);
  static size_t const findEntity(uint32_t ID);

  static std::vector<uint32_t> getEntityList();

  private:
  static std::vector<uint32_t> validEntities;
  static uint32_t m_entityCount;

};

}
}

#endif



