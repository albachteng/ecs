#include "Entity.cpp"
#include "Terrain.cpp"
#include "Vec2.h"
#include "iostream"
#include <algorithm>

int main() {
  // Vec2 v1 = Vec2(1.0, 1.0);
  // v1.print_vec2();
  // Vec2 v2 = Vec2(2.0, 2.0);
  // v2.print_vec2();
  // Vec2 v3;
  // v3 = v1 + v2;
  // v3.print_vec2();
  // v1 += v2;
  // v1.print_vec2();
  Terrain *t1 = new Terrain(1);
  Terrain *t2 = new Terrain(2);
  Terrain *t3 = new Terrain(3);
  t1->printTerrain();
  t2->printTerrain();
  t3->printTerrain();
  World *w = new World();
  Terrain **tiles = w->getTiles();
  for (int i = 0; i < w->getHeight(); i++) {
    for (int j = 0; j < w->getWidth(); j++) {
      tiles[i][j].printTerrain();
    }
  }
}

// TODO
void sRender(std::vector<Entity> &entities) {
  for (auto &e : entities) {
    if (e.cTransform && e.cShape) { // TODO: bitset filter
      e.cTransform->pos += e.cTransform->vel;
      e.cShape->shape.setPosition(e.cTransform->pos);
      window.draw(e.cShape->shape);
    }
  }
};

void sMovement(std::vector<Entity> &entities) {
  for (auto &e : entities) {
    if (e.cTransform) { // TODO: bitset filter
      e.cTransform->pos += e.cTransform->vel;
    }
  }
};

// TODO - collisions
void sPhysics(std::vector<Entity> &entities){};
