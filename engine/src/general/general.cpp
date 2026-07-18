
#include "general.hpp"

using namespace secret;

Vec4::Vec4() {
  x=0;
  y=0;
  z=0;
  w=0;
}
Vec4::Vec4(float x, float y, float z, float w) {
  this->x=x;
  this->y=y;
  this->z=z;
  this->w=w;
}

Vec4 Vec4::operator+(Vec4 other) {
  return Vec4(x+other.x, y+other.y, z+other.z, w+other.w); 
}
Vec4 Vec4::operator-(Vec4 other) {
  return Vec4(x-other.x, y-other.y, z-other.z, w-other.w); 
}
Vec4 Vec4::operator/(Vec4 other) {
  return Vec4(x/other.x, y/other.y, z/other.z, w/other.w); 
}
Vec4 Vec4::operator*(Vec4 other) {
  return Vec4(x*other.x, y*other.y, z*other.z, w*other.w); 
}
Vec4 Vec4::scale(float scalar) {
  return Vec4(x*scalar, y*scalar, z*scalar, w*scalar); 
}

Vec2::Vec2() {
  x=0;
  y=0;
}
Vec2::Vec2(float x, float y) {
  this->x=x;
  this->y=y;
}

Vec2 Vec2::operator+(Vec2 other) {
  return Vec2(x+other.x, y+other.y); 
}
Vec2 Vec2::operator-(Vec2 other) {
  return Vec2(x-other.x, y-other.y); 
}
Vec2 Vec2::operator*(Vec2 other) {
  return Vec2(x*other.x, y*other.y); 
}
Vec2 Vec2::operator/(Vec2 other) {
  return Vec2(x/other.x, y/other.y); 
}
Vec2 Vec2::scale(float scalar) {
  return Vec2{this->x * scalar, this->y * scalar};
}

Rect::Rect() {
  this->pos = {0,0};
}
Rect::Rect(Vec2 pos, float width, float height) {
  this->pos = pos;
  this->width = width;
  this->height = height;
}

Circle::Circle() {
  this->pos = {0,0};
}
Circle::Circle(Vec2 pos, float radius) {
  this->pos = {0,0};
  this->radius = radius;
}

Color::Color(int r, int g, int b) {
  this->r=r;
  this->g=g;
  this->b=b;
}
Color::Color() {

}
