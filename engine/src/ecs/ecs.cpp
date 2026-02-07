#include "ecs.hpp"
#include "../ELOgine.hpp"
#include <cstdint>

#include <string>

using namespace elo;
using namespace ecs;

std::vector<uint32_t> EntitySys::validEntities = std::vector<uint32_t>();
uint32_t EntitySys::m_entityCount = 0;

uint32_t EntitySys::addEntity(Transform init) {
  uint32_t ID = m_entityCount;
  validEntities.push_back(ID);
  m_entityCount++;

  TransformComponent::add(ID, init);

  return ID;
}
void EntitySys::remEntity(uint32_t entityID) {
  validEntities[findEntity(entityID)] = std::move(validEntities.back());
  validEntities.pop_back();
}
size_t const EntitySys::findEntity(uint32_t ID) {
  for (size_t i = 0; i < validEntities.size(); i++) {
    if (validEntities[i] == ID) {
      return i;
    }
  }
  return -1;
}
std::vector<uint32_t> EntitySys::getEntityList() {
  return validEntities;
}


// Transform
std::unordered_map<uint32_t, Transform> TransformComponent::entityList = std::unordered_map<uint32_t, Transform>();
Transform::Transform(Vector2 pos, float width, float height){
  this->pos=pos;
  this->width=width;
  this->height=height;
}
Transform::Transform(Vector2 pos, float radius) {
  this->pos=pos;
  this->radius=radius;
}
void TransformComponent::add(uint32_t entityID, Transform transformInit) {
  entityList.emplace(entityID, transformInit);
}
void TransformComponent::rem(uint32_t entityID) {
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

// IMG Renderer 
std::unordered_map<uint32_t, ImgRenderer> ImgRendererComp::entityList = std::unordered_map<uint32_t, ImgRenderer>();
ImgRenderer::ImgRenderer(std::string location, SDL_FRect uv, int layer) {
  texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
};
ImgRenderer::ImgRenderer(std::string location, int layer) {
  texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
};
void ImgRendererComp::add(uint32_t entityID, ImgRenderer ir) {
  entityList.emplace(entityID, ir);
}
void ImgRendererComp::rem(uint32_t entityID) {
  entityList.erase(entityID);
}
ImgRenderer& ImgRendererComp::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const ImgRendererComp::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}
std::unordered_map<uint32_t, ImgRenderer> ImgRendererComp::getEntityList() {
  return entityList;
};

// Primitive Renderer
std::unordered_map<uint32_t, PrimitiveRenderer> PrimitiveRendererComponent::entityList = std::unordered_map<uint32_t, PrimitiveRenderer>();
PrimitiveRenderer::PrimitiveRenderer(PrimitiveType type, Color color) {
  this->type=type;
  this->color=color;
};
void PrimitiveRendererComponent::add(uint32_t entityID, PrimitiveRenderer pr) {
  entityList.emplace(entityID, pr);
}
void PrimitiveRendererComponent::rem(uint32_t entityID) {
  entityList.erase(entityID);
}
PrimitiveRenderer& PrimitiveRendererComponent::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const PrimitiveRendererComponent::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}
std::unordered_map<uint32_t, PrimitiveRenderer> PrimitiveRendererComponent::getEntityList() {
  return entityList;
};



