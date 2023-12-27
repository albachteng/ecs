#include "Vec2.h"
#include "iostream"

Vec2::Vec2() : x(0.0f), y(0.0f){};
Vec2::Vec2(float x, float y) : x(x), y(y){};

const Vec2 Vec2::operator+(const Vec2 &rhs) {
  return Vec2(this->x + rhs.x, this->y + rhs.y);
};

Vec2 &Vec2::operator+=(const Vec2 &rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
};

void Vec2::print_vec2() {
  std::cout << "X: " << this->x << " Y: " << this->y << "\n" << std::endl;
}
