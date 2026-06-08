
#include "math.hpp"
#include "../HUGE.hpp"

#include <cmath>
#include <vector>

namespace huge {
namespace math {

float vectorLength(Vec2 a) {
  return sqrt(a.x * a.x+a.y * a.y);
}

float vectorDistance(Vec2 a, Vec2 b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;

  return sqrt(dx*dx+dy*dy);
}

Vec2 vectorNormalize(Vec2 a) {
  float len = vectorLength(a);

  return Vec2((a.x/len),(a.y/len));
}  

float vectorDot(Vec2 a, Vec2 b) {
  return a.x*b.x + a.y*b.y;
}

float vectorCross(Vec2 a, Vec2 b) {
  return a.x * b.y - a.y * b.x;
}

float vectorSlope(Vec2 a, Vec2 b) {
  return (b.y - a.y)/(b.x - a.x);
}


}
}
