#pragma once
#include "Vec2.cpp"

typedef struct CBBox {
  Vec2 min, max;
  // TODO:
  Vec2 size;
  Vec2 halfSize;
  // CBBox();
  // CBBox(const Vec2 &min, const Vec2 &max);
} CBBox;
