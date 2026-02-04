#ifndef _ECS_HPP
#define _ECS_HPP

#include <functional>
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <cstdint>
#include <string>
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
  float x, y;
};

// transform component
struct Transform {
  Transform(Vector2 position, float rotation, float height, float width);
  Vector2 position;
  float rotation;
  float height;
  float width;
};

class TransformComponent {
public:
  void remove(uint32_t entityID);
  void add(uint32_t entityID, Transform transformInit);
  Transform &get(uint32_t entityID);
  bool const has(uint32_t entityID);
private:
  std::unordered_map<uint32_t, Transform> entityList;
};

// renderer component
struct Renderer {
  Renderer(SDL_Texture *texture, SDL_FRect uv, int layer);
  SDL_Texture *texture;
  SDL_FRect uv;
  int layer;
};

class RendererComponent {
public:
  void remove(uint32_t entityID);
  void add(uint32_t entityID, Renderer rendererInit);
  Renderer &get(uint32_t entityID);
  bool const has(uint32_t entityID);
private:
  std::unordered_map<uint32_t, Renderer> entityList;
};

// text renderer component 
struct TextRenderer {
  int size;
  SDL_Texture *texture;
  std::string text;
  std::string fontFileLocation;
  SDL_Color textFG;
};

class TextRendererComponent {
public:
  void remove(uint32_t entityID);
  void add(uint32_t entityID, TextRenderer rendererInit);
  TextRenderer& get(uint32_t entityID);
  bool const has(uint32_t entityID);
private:
  std::unordered_map<uint32_t, TextRenderer> entityList;
};

// SDLSquare
struct SDLSquare{
  SDLSquare(SDL_FRect offset, SDL_Color color);
  SDL_Color color;
  SDL_FRect offset;
};

class SDLSquareComponent{
public:
  void remove(uint32_t entityID);
  void add(uint32_t entityID, SDLSquare SDLSOInit);
  SDLSquare& get(uint32_t entityID);
  bool const has(uint32_t entityID);
private:
  std::unordered_map<uint32_t, SDLSquare> entityList;
};

// SDLSquareOutline
struct SDLSquareOutline{
  SDLSquareOutline(SDL_FRect offset, SDL_Color color);
  SDL_Color color;
  SDL_FRect offset;
};

class SDLSquareOutlineComponent{
public:
  void remove(uint32_t entityID);
  void add(uint32_t entityID, SDLSquareOutline SDLSOInit);
  SDLSquareOutline& get(uint32_t entityID);
  bool const has(uint32_t entityID);
private:
  std::unordered_map<uint32_t, SDLSquareOutline> entityList;
};

// Collider
struct Collider{
  Collider(SDL_FRect offset);
  SDL_FRect offset;

  bool isTrigger;
  std::function<void()> onTrigger;
};

class ColliderComponent{
public:
  void remove(uint32_t entityID);
  void add(uint32_t entityID, Collider SDLSOInit);
  Collider& get(uint32_t entityID);
  bool const has(uint32_t entityID);
private:
  std::unordered_map<uint32_t, Collider> entityList;
};

// RigidBody
struct RigidBody{
  RigidBody();

  bool gravityEnabled;

  Vector2 vel;
  Vector2 acc;
  float mass;

  void addForce(Vector2 f);

};

class RigidBodyComponent{
public:
  void remove(uint32_t entityID);
  void add(uint32_t entityID, RigidBody SDLSOInit);
  RigidBody& get(uint32_t entityID);
  bool const has(uint32_t entityID);
  float entityMaxSpeed;
private:
  std::unordered_map<uint32_t, RigidBody> entityList;
};

// PlayerController
struct PlayerCtrl{

};

class PlayerCtrlComponent{
public:
  void remove(uint32_t entityID);
  void add(uint32_t entityID, PlayerCtrl SDLSOInit);
  PlayerCtrl& get(uint32_t entityID);
  bool const has(uint32_t entityID);

private:
  std::unordered_map<uint32_t, PlayerCtrl> entityList;
};


// main class
class EntitySys {
  friend class core::Elogine;
  friend class render::RenderSys;
public:
  EntitySys(float s);

  uint32_t createEntity(Transform initTransform);
  void removeEntity(uint32_t entityID);

  size_t const findEntity(uint32_t entityID);

  TransformComponent transformComponent;

  TextRendererComponent textRendererComponent;
  RendererComponent rendererComponent;

  SDLSquareComponent sdlSquareComponent;
  SDLSquareOutlineComponent sdlSquareOutlineComponent;

  ColliderComponent colliderComponent;
  RigidBodyComponent rigidBodyComponent;
  PlayerCtrlComponent playerCtrlComponent;
  

private:
  std::vector<uint32_t> validEntities;
  uint32_t entityCount;
};

} // namespace ecs
} // namespace engine

#endif
