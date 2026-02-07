#ifndef _GENERAL_HPP
#define _GENERAL_HPP

#include <vector>

namespace elo {
struct Vector2 {
  
  float x;
  float y;

  Vector2();
  Vector2(float x, float y);

  Vector2 operator+(Vector2 other);
  Vector2 operator-(Vector2 other);
  Vector2 operator*(Vector2 other);
  Vector2 operator/(Vector2 other);

};

struct Color {
  int r;
  int g;
  int b;
  
  Color(int r, int g, int b);
  Color();
};
}

#endif
