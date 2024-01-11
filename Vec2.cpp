#include "Vec2.h"
#include "iostream"

Vec2::Vec2() : x(0.0f), y(0.0f){};
Vec2::Vec2(float x, float y) : x(x), y(y){};

const Vec2 Vec2::operator+(const Vec2 &rhs) {
  return Vec2(this->x + rhs.x, this->y + rhs.y);
};

const Vec2 Vec2::operator-(const Vec2 &rhs) {
  return Vec2(this->x - rhs.x, this->y - rhs.y);
};

const Vec2 Vec2::operator*(float scale) {
  return Vec2(this->x * scale, this->y * scale);
};

const float Vec2::X() { return x; }

const float Vec2::Y() { return y; }

Vec2 &Vec2::operator+=(const Vec2 &rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
};

Vec2 &Vec2::operator-=(const Vec2 &rhs) {
  x -= rhs.x;
  y -= rhs.y;
  return *this;
};

Vec2 &Vec2::operator*=(float scale) {
  x *= scale;
  y *= scale;
  return *this;
};

void Vec2::print_vec2() {
  std::cout << "X: " << x << " Y: " << y << "\n" << std::endl;
}
