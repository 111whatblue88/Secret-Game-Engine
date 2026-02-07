#ifndef _ECS_HPP
#define _ECS_HPP

#include "../general/general.hpp"

#include <string>
#include <SDL3/SDL.h>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace elo {
namespace ecs {

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
  static void rem(uint32_t entity);
  static Transform& get(uint32_t entity); 
  static const bool has(uint32_t entity);

  private:
  static std::unordered_map<uint32_t, Transform> entityList; 
};

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



