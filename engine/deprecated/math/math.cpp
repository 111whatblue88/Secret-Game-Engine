
#include "../elogine.hpp"

#include <cmath>
#include <vector>


namespace engine {
namespace math {

float vectorLength(ecs::Vector2 a) {
  return sqrt(a.x * a.x+a.y * a.y);
}

float vectorDistance(ecs::Vector2 a, ecs::Vector2 b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;

  return sqrt(dx*dx+dy*dy);
}

ecs::Vector2 vectorNormalize(ecs::Vector2 a) {
  float len = vectorLength(a);

  return ecs::Vector2((a.x/len),(a.y/len));
}  

float vectorDot(ecs::Vector2 a, ecs::Vector2 b) {
  return a.x*b.x + a.y*b.y;
}

float vectorCross(ecs::Vector2 a, ecs::Vector2 b) {
  return a.x * b.y - a.y * b.x;
}



}
}
