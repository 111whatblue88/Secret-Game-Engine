#include "ecs.hpp"
#include "../elogine.hpp"

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <vector>

namespace engine {
namespace ecs {

uint32_t EntitySys::createEntity(Transform initTransform) {
  uint32_t ID = entityCount;
  validEntities.push_back(ID);
  entityCount++;

  transformComponent.add(ID, initTransform);

  return ID;
}

size_t const EntitySys::findEntity(uint32_t entityID) {
  for (size_t i = 0; i < validEntities.size(); i++) {
    if (validEntities[i] == entityID) {
      return i;
    }
  }
  return -1;
}

void EntitySys::removeEntity(uint32_t entityID) {
  validEntities[findEntity(entityID)] = std::move(validEntities.back());
  validEntities.pop_back();
}

Transform::Transform(Vector2 position, float rotation, float height, float width) {
  this->position = position;
  this->rotation = rotation;
  this->height = height;
  this->width = width;
}

void TransformComponent::add(uint32_t entityID, Transform transformInit) {
  entityList.emplace(entityID, transformInit);
}
void TransformComponent::remove(uint32_t entityID) {
  entityList.erase(entityID);
}
Transform &TransformComponent::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const TransformComponent::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}

Renderer::Renderer(SDL_Texture *texture, SDL_FRect uv, int layer) {
  this->texture = texture;
  this->uv = uv;
  this->layer = layer;
}
void RendererComponent::add(uint32_t entityID, Renderer rendererInit) {
  entityList.emplace(entityID, rendererInit);
}
void RendererComponent::remove(uint32_t entityID) {
  entityList.erase(entityID);
}
Renderer &RendererComponent::get(uint32_t entityID) {
  return entityList.at(entityID);
};
bool const RendererComponent::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}

void TextRendererComponent::add(uint32_t entityID, TextRenderer rendererInit) {
  entityList.emplace(entityID, rendererInit);
}
void TextRendererComponent::remove(uint32_t entityID) {
  entityList.erase(entityID);
}
TextRenderer& TextRendererComponent::get(uint32_t entityID) {
  return entityList.at(entityID);
};
bool const TextRendererComponent::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}


} // namespace ecs
} // namespace engine
