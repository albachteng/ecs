#pragma once
#include "Vec2.h"

// TODO: use sf::Vec2?
class CTransform {
public:
  Vec2 pos = {0, 0};
  // TODO
  // Vec2 prevPos = {0, 0};
  // Vec2 scale = {1.0, 1.0};
  Vec2 vel = {0, 0};
  float angle = 0;
  CTransform();
  CTransform(const Vec2 &p, const Vec2 &v);
};
