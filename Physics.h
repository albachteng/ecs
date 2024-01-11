#pragma once
#include "CBBox.h"
#include "Entity.cpp"
#include <cmath>

class Physics {
  // circle collision
public:
  static bool isCollision(std::shared_ptr<Entity> first,
                          std::shared_ptr<Entity> second) {
    if (first->cShape && second->cShape) {
      //(x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
      float cSquared =
          pow((second->cTransform->pos.x - first->cTransform->pos.x), 2) +
          pow(second->cTransform->pos.y - first->cTransform->pos.y, 2);
      return std::sqrt(cSquared) <=
             (second->cShape->radius + first->cShape->radius);
    }
    return false;
  };

  // BBox-point contains
  static bool contains(CBBox &box, Vec2 &point) {
    return box.min.X() < point.X() && box.max.X() >= point.X() &&
           box.min.Y() < point.Y() && box.max.Y() > point.Y();
  };

  // 4-corners collision
  static bool intersects(CBBox &first, CBBox &second) {
    Vec2 *topRight = new Vec2(second.min.X(), second.max.Y());
    Vec2 *bottomLeft = new Vec2(second.max.X(), second.min.Y());
    return contains(first, second.min) || contains(first, second.max) ||
           contains(first, *topRight) || contains(first, *bottomLeft);
  }

  // TOP-LEFT corner and WIDTH/HEIGTH collision detection
  // (Q: does this account for +y being down?)
  static bool isCollision(CBBox &first, CBBox &second) {
    float h1 = first.min.y - first.max.y;
    float h2 = second.min.y - first.max.y;
    float w1 = second.max.x - first.min.x;
    float w2 = second.max.x - first.min.x;
    return first.min.y < second.min.y + h2 && second.min.y < first.min.y + h1 &&
           // VERTICAL OVERLAP
           first.min.x < second.min.x + w2 && second.min.x < first.min.x + w1;
    //
  }
};
