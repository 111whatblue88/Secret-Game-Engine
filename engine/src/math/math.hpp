#ifndef _MATH_HPP
#define _MATH_HPP

#include "../general/general.hpp"

namespace elo{
namespace math {
  
  float vectorLength(Vector2 a);
  float vectorDistance(Vector2 a, Vector2 b);

  Vector2 vectorNormalize(Vector2 a);  

  float vectorDot(Vector2 a, Vector2 b);
  float vectorCross(Vector2 a, Vector2 b);
  
  float vectorSlope(Vector2 a, Vector2 b);
}
}



#endif




