#include "Vec2.h"

// TODO: use sf::Vec2?
class CTransform {
public:
  Vec2 pos = {0, 0};
  Vec2 vel = {0, 0};
  CTransform();
  CTransform(const Vec2 &p, const Vec2 &v);
};
