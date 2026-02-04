#ifndef _MATH_HPP
#define _MATH_HPP

#include <vector>
#include <cmath>

namespace engine {
namespace ecs {
  struct Vector2;
}
namespace math {
  
  float vectorLength(ecs::Vector2 a);
  float vectorDistance(ecs::Vector2 a, ecs::Vector2 b);

  ecs::Vector2 vectorNormalize(ecs::Vector2 a);  

  float vectorDot(ecs::Vector2 a, ecs::Vector2 b);
  float vectorCross(ecs::Vector2 a, ecs::Vector2 b);

}
}



#endif




