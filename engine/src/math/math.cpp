
#include "../ELOgine.hpp"

#include <cmath>
#include <vector>

namespace elo {
namespace math {

float vectorLength(Vector2 a) {
  return sqrt(a.x * a.x+a.y * a.y);
}

float vectorDistance(Vector2 a, Vector2 b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;

  return sqrt(dx*dx+dy*dy);
}

Vector2 vectorNormalize(Vector2 a) {
  float len = vectorLength(a);

  return Vector2((a.x/len),(a.y/len));
}  

float vectorDot(Vector2 a, Vector2 b) {
  return a.x*b.x + a.y*b.y;
}

float vectorCross(Vector2 a, Vector2 b) {
  return a.x * b.y - a.y * b.x;
}



}
}
