#ifndef _MATH_HPP
#define _MATH_HPP

#include "../general/general.hpp"

namespace secret {
namespace math {
  
  float vectorLength(Vec2 a);
  float vectorDistance(Vec2 a, Vec2 b);

  Vec2 vectorNormalize(Vec2 a);  

  float vectorDot(Vec2 a, Vec2 b);
  float vectorCross(Vec2 a, Vec2 b);
  
  float vectorSlope(Vec2 a, Vec2 b);

}
}



#endif




