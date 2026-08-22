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

//TODO: implement functionality for this and replace GLM code with it
struct mat4 {

  float matrix[4][4];

  mat4(float mat4[4][4]);
  mat4();

  mat4 operator*(Vec2 other);
  mat4 operator*(mat4 other);

};

struct Vec4 {
  
  float x;
  float y;
  float z;
  float w;

  Vec4();
  Vec4(float x, float y, float z, float w);

  Vec4 operator+(Vec4 other);
  Vec4 operator-(Vec4 other);
  Vec4 operator*(Vec4 other);
  Vec4 operator/(Vec4 other);

  Vec4 scale(float scalar);

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
