
#include "general.hpp"

using namespace huge;

Vector2::Vector2() {

}
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
Vector2 Vector2::scale(float scalar) {
  return Vector2{this->x * scalar, this->y * scalar};
}

Color::Color(int r, int g, int b) {
  this->r=r;
  this->g=g;
  this->b=b;
}
Color::Color() {

}
