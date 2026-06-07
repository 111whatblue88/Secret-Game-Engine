#ifndef _GENERAL_HPP
#define _GENERAL_HPP

#include <vector>

namespace huge {
struct Vector2 {
  
  float x;
  float y;

  Vector2();
  Vector2(float x, float y);

  Vector2 operator+(Vector2 other);
  Vector2 operator-(Vector2 other);
  Vector2 operator*(Vector2 other);
  Vector2 operator/(Vector2 other);

  Vector2 scale(float scalar);

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
