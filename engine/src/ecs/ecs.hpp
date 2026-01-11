#ifndef _ECS_HPP
#define _ECS_HPP

#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace engine {
namespace render {
  class RenderSys;
}
namespace core {
  class Elogine;
}
namespace ecs {

  struct Vector2 {
    int x, y;
  };

  //transform component
  struct Transform {
    Transform(Vector2 position, float rotation, Vector2 size);
    Vector2 position;
    float rotation;
    Vector2 size;
  };

  class TransformComponent {
  public:

    void remove(uint32_t entityID);
    void add (uint32_t entityID, Transform transformInit);
    Transform& get(uint32_t entityID);
    bool const has(uint32_t entityID);

  private:
    std::unordered_map<uint32_t, Transform> entityList;
  };

  struct Renderer {
    Renderer(SDL_Texture* texture, SDL_FRect uv, int layer);
    SDL_Texture* texture;
    SDL_FRect uv;
    int layer;
  };

  class RendererComponent {
  public:

    void remove(uint32_t entityID);
    void add (uint32_t entityID, Renderer rendererInit);
    Renderer& get(uint32_t entityID);
    bool const has(uint32_t entityID);

  private:
    std::unordered_map<uint32_t, Renderer> entityList;
  };

  class EntitySys {
  friend class core::Elogine;
  friend class render::RenderSys;
  public:

    uint32_t createEntity(Transform initTransform);
    void removeEntity(uint32_t entityID);

    size_t const findEntity(uint32_t entityID);

    TransformComponent transformComponent;
    RendererComponent rendererComponent;

  private:

    std::vector<uint32_t> validEntities;
    uint32_t entityCount;

  };

}
}

#endif




