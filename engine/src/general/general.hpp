#ifndef _GENERAL_HPP
#define _GENERAL_HPP

#include <vector>

namespace secret {
struct Vec2 {
  
  float x;
  float y;

  Vec2();
  Vec2(float x, float y);

  Vec2 operator+(Vec2 other);
  Vec2 operator-(Vec2 other);
  Vec2 operator*(Vec2 other);
  Vec2 operator/(Vec2 other);

  Vec2 scale(float scalar);

};

struct Rect {

  Vec2 pos;
  float width;
  float height;

  Rect();
  Rect(Vec2 pos, float width, float height);

};

struct Circle {
  Vec2 pos;
  float radius;

  Circle();
  Circle(Vec2 pos, float radius);
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
