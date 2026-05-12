#include "ecs.hpp"
#include "../HUGE.hpp"
#include <SDL3/SDL_pixels.h>
#include <algorithm>
#include <cstdint>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

using namespace huge;
using namespace ecs;

ecs::ComponentList<Transform> EntitySys::TransformComp = ecs::ComponentList<Transform>();
ecs::ComponentList<TextRenderer> EntitySys::TextRendererComp = ecs::ComponentList<TextRenderer>();
ecs::ComponentList<PrimitiveRenderer> EntitySys::PrimitiveRendererComp= ecs::ComponentList<PrimitiveRenderer>();
ecs::ComponentList<ImgRenderer> EntitySys::ImgRendererComp= ecs::ComponentList<ImgRenderer>();
ecs::ComponentList<BasicCollider> EntitySys::BasicColliderComp= ecs::ComponentList<BasicCollider>();
ecs::ComponentList<PhysicsBody> EntitySys::PhysicsBodyComp= ecs::ComponentList<PhysicsBody>();

std::vector<uint32_t> EntitySys::validEntities = std::vector<uint32_t>();
uint32_t EntitySys::m_entityCount = 0;

uint32_t EntitySys::createEntity(Transform transform) {
  m_entityCount++;
  validEntities.push_back(m_entityCount);
  TransformComp.add(m_entityCount, transform);
  return m_entityCount;
}
std::vector<uint32_t> ecs::EntitySys::getEntityList() {
  return validEntities;
}

// Transform
Transform::Transform(Vector2 pos, float width, float height){
  this->pos=pos;
  this->width=width;
  this->height=height;
  ID=EntitySys::TransformComp.getComponentCount()+1;
}
Transform::Transform(Vector2 pos, float radius) {
  this->pos=pos;
  this->radius=radius;
}
Transform::Transform() {
  this->pos={0,0};
  this->width=0;
  this->height=0;
  this->radius=0;
}
uint32_t Transform::getID() {
  return ID;
}

// IMG Renderer 
ImgRenderer::ImgRenderer(std::string location, SDL_FRect uv, int layer) {
  texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
};
ImgRenderer::ImgRenderer(std::string location, int layer) {
  texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv={0,0,0,0};
};

// Text Renderer 
TextRenderer::TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer)
  :transform(Vector2(0,0),0,0)
{
  this->texture = rend::RenderSys::m_renderer.textureFromFont(
      fontLocation,
      size,
      color,
      text
  );
  this->layer=layer;
  this->inheritTransform = true;
};
uint32_t TextRenderer::getID() {
  return ID;
}

TextRenderer::TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer, Transform t)
  :transform(t)
{
  this->texture = rend::RenderSys::m_renderer.textureFromFont(
      fontLocation,
      size,
      color,
      text
  );
  this->layer=layer;
  this->inheritTransform = false;
};

bool TextRenderer::editText(std::string fontLocation, std::string text, int size, Color color) {
  this->texture = rend::RenderSys::m_renderer.textureFromFont(
      fontLocation,
      size,
      color,
      text
  );
  return true;
}

// Primitive Renderer
PrimitiveRenderer::PrimitiveRenderer(PrimitiveType type, Color color) {
  this->type=type;
  this->color=color;
};
PrimitiveRenderer::PrimitiveRenderer(PrimitiveType type, Color color, Vector2 vec) {
  this->type=type;
  this->LineTypeSecondPoint=vec;
  this->color=color;
}


// PhysicsBody
PhysicsBody::PhysicsBody() {
  this->velocity = {0,0};
}
void PhysicsBody::PhysicsBody::addForce(Vector2 force) {
  velocity.x += force.x;
  velocity.y += force.y;
}

// basicCollider
BasicCollider::BasicCollider(Collidertype type, bool renderCollider) {
  this->type = type;
  this->renderCollider = renderCollider;
}
BasicCollider::BasicCollider(Collidertype type) {
  this->type = type;
  this->renderCollider = false;
}
BasicCollider::BasicCollider() {
  this->type = BasicCollider::Collidertype::lineCollider;
  this->renderCollider = false;
}

bool EntitySys::updateComponents() {
  
  // loop through every transform component 
  //
  // loop through every collider and check if it collides with any other colliders 
  // if so, check if either has a phyiscsbody, and if either do check if they have static true
  // if static is true, that one will not be able to be pushed, if neither do transfer its velocity to the other object
  //
  // 50% chance this works
  //

  auto& TList = EntitySys::TransformComp.getComponentList();
  auto& BCList = EntitySys::BasicColliderComp.getComponentList();


  // TODO: NONE of this works redo it all 

  auto EList = EntitySys::getEntityList();

  for (auto E : EList) {
    auto& T = EntitySys::TransformComp.get(E);
    if (EntitySys::BasicColliderComp.has(E)) {
      if (!EntitySys::PhysicsBodyComp.has(E)) {
        continue;
      }
      auto& BC1 = EntitySys::BasicColliderComp.get(E);
      for (auto& BC2 : BCList) {
        if (E == BC2.first) {
          continue;
        }
        if (!EntitySys::PhysicsBodyComp.has(BC2.first)) {
          continue;
        }
        auto& T2 = EntitySys::TransformComp.get(BC2.first);

        auto& PB1 = EntitySys::PhysicsBodyComp.get(E);
        auto& PB2 = EntitySys::PhysicsBodyComp.get(BC2.first);

        // first check for square on square
        // then check for circle on square
        // then check for circle on line 
        // then check for square on line

        if (BC1.type == BasicCollider::Collidertype::boxCollider &&
        BC2.second.type == BasicCollider::Collidertype::boxCollider
        ) {
          std::cout << "checking\n";
          if (math::boxOnBoxColliding(
            T.pos,T.width,T.height,
            T2.pos,T2.width,T2.height
          )) {
            //they are colliding
            //
            std::cout << "collision detected\n";
            std::cout << "before1 " << PB1.velocity.x << " " << PB1.velocity.y << "\n";
            std::cout << "before2 " << PB2.velocity.x << " " << PB2.velocity.y << "\n";
            if (PB1.isStatic) {
              std::cout << "static 1 found\n";
              PB2.velocity = {-PB2.velocity.x, -PB2.velocity.y};
            } else if (PB2.isStatic) {
              std::cout << "static 2 found\n";
              PB1.velocity = {-PB1.velocity.x, -PB1.velocity.y};
            }
            std::cout << "after1 " << PB1.velocity.x << " " << PB1.velocity.y << "\n";
            std::cout << "after2 " << PB2.velocity.x << " " << PB2.velocity.y << "\n";



          }
          continue;
        } 





      }
        /*
        // if bc1 = circle && bc2 = box OR bc1 = box & bc2 = circle
        if (BC1.type == BasicCollider::Collidertype::circleCollider && 
        BC2.second.type == BasicCollider::Collidertype::boxCollider ||
        BC2.second.type == BasicCollider::Collidertype::circleCollider && 
        BC1.type == BasicCollider::Collidertype::boxCollider
        ) {
          // one box one square

          break;
        }
        if (BC1.type == BasicCollider::Collidertype::lineCollider &&
        BC2.second.type == BasicCollider::Collidertype::circleCollider ||
        BC1.type == BasicCollider::Collidertype::circleCollider &&
        BC2.second.type == BasicCollider::Collidertype::lineCollider
        ) {
          // one line one circle
          break;
        } 
        if (BC1.type == BasicCollider::Collidertype::lineCollider &&
        BC2.second.type == BasicCollider::Collidertype::boxCollider ||
        BC1.type == BasicCollider::Collidertype::boxCollider &&
        BC2.second.type == BasicCollider::Collidertype::lineCollider
        ) {
          // one line one box
          break;
        } 
        */
    }

    // update velocity
    if (EntitySys::PhysicsBodyComp.has(E)) {
      auto& PB = EntitySys::PhysicsBodyComp.get(E);
      T.pos.x += PB.velocity.x;
      T.pos.y += PB.velocity.y;
    }




  }


  return true;
};



