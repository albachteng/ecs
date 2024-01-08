#include "Vec2.h"
class CBBox {
  Vec2 min, max;

public:
  CBBox();
  CBBox(const Vec2 &min, const Vec2 &max);
  bool contains(Vec2 &point);
  bool intersects(CBBox &other);
};
