#pragma once

class Vec2 {
private:
public:
  float x, y;
  Vec2();
  Vec2(float x, float y);
  const float X(), Y();
  const Vec2 operator+(const Vec2 &rhs);
  Vec2 &operator+=(const Vec2 &rhs);
  void print_vec2();
};
