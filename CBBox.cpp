#include "CBBox.h"
#include <iostream>

CBBox::CBBox() { std::cout << "default bbox" << std::endl; };

CBBox::CBBox(const Vec2 &min, const Vec2 &max) : min(min), max(max) {
  std::cout << "making bbox" << std::endl;
};

bool CBBox::contains(Vec2 &point) {
  return min.X() < point.X() && max.X() >= point.X() && min.Y() < point.Y() &&
         max.Y() > point.Y();
}

bool CBBox::intersects(CBBox &other) {
  Vec2 *topRight = new Vec2(other.min.X(), other.max.Y());
  Vec2 *bottomLeft = new Vec2(other.max.X(), other.min.Y());
  return contains(other.min) || contains(other.max) || contains(*topRight) ||
         contains(*bottomLeft);
}
