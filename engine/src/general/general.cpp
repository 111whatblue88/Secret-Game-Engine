
#include "general.hpp"

using namespace huge;

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
