
#include "math.hpp"
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

float vectorSlope(Vector2 a, Vector2 b) {
  return (b.y - a.y)/(b.x - a.x);
}

bool boxOnBoxColliding(Vector2 boxPos1, int boxWidth1, int boxHeight1, Vector2 boxPos2, int boxWidth2, int boxHeight2) {
  if (
    boxPos1.x < boxPos2.x + boxWidth2 &&
    boxPos1.x + boxWidth1 > boxPos2.x && 
    boxPos1.y < boxPos2.y + boxHeight2 &&
    boxPos1.y + boxHeight1 > boxPos2.y
  ) {
    return true;
  } else {
    return false;
  }
}




}
}
