#ifndef _MATH_HPP
#define _MATH_HPP

#include "../general/general.hpp"

namespace huge{
namespace math {
  
  float vectorLength(Vector2 a);
  float vectorDistance(Vector2 a, Vector2 b);

  Vector2 vectorNormalize(Vector2 a);  

  float vectorDot(Vector2 a, Vector2 b);
  float vectorCross(Vector2 a, Vector2 b);
  
  float vectorSlope(Vector2 a, Vector2 b);

  bool boxOnCircleColliding(
  Vector2 boxPos, int boxWidth, int boxHeight, 
  Vector2 circlePos, float circleRadius
  );
  bool boxOnBoxColliding(
  Vector2 boxPos1, int boxWidth1, int boxHeight1, 
  Vector2 boxPos2, int boxWidth2, int boxHeight2
  );
  bool boxOnLineColliding(
  Vector2 boxPos, int boxWidth, int boxHeight, 
  Vector2 linePos
  );
  bool circleOnLineColliding(
  Vector2 circlePos, float circleRadius,
  Vector2 linePos
  );
  bool circleOnCircleColliding(
  Vector2 circlePos1, float circleRadius1,
  Vector2 circlePos2, float circleRadius2
  );



}
}



#endif




