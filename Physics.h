#pragma once
#include "Entity.cpp"

class Physics {
public:
  static bool isCollision(std::shared_ptr<Entity> first,
                          std::shared_ptr<Entity> second) {
    if (first->cShape && second->cShape) {
      //(x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
      return pow((second->cTransform->pos.x - first->cTransform->pos.x), 2) +
                 pow(second->cTransform->pos.y - first->cTransform->pos.y, 2) <=
             pow(second->cShape->radius + first->cShape->radius, 2);
    }
    return false;
  };
};
