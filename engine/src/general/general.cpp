
#include "general.hpp"

using namespace elo;

Vector2::Vector2(float x, float y) {
  this->x=x;
  this->y=y;
}

Vector2 Vector2::operator+(Vector2 other) {
  return Vector2(x+other.x, y+other.y); 
}
Vector2 Vector2::operator-(Vector2 other) {
  return Vector2(x-other.x, y-other.y); 
}
Vector2 Vector2::operator*(Vector2 other) {
  return Vector2(x*other.x, y*other.y); 
}
Vector2 Vector2::operator/(Vector2 other) {
  return Vector2(x/other.x, y/other.y); 
}

Color::Color(int r, int g, int b) {
  this->r=r;
  this->g=g;
  this->b=b;
}
