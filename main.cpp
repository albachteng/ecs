#include "CBBox.h"
// #include "Entity.cpp"
#include "Terrain.cpp"
#include "iostream"
#include <algorithm>
#include <ostream>

using std::endl;

int main() {
  Vec2 *v1 = new Vec2(2, 2);
  Vec2 *v2 = new Vec2(4, 4);
  Vec2 *v3 = new Vec2(1, 3);
  Vec2 *v4 = new Vec2(3, 5);
  Vec2 *v5 = new Vec2(9, 9);
  Vec2 *v6 = new Vec2(10, 10);
  CBBox *box1 = new CBBox(*v1, *v2);
  CBBox *box2 = new CBBox(*v3, *v4);
  CBBox *box3 = new CBBox(*v5, *v6);
  std::cout << box1->contains(*v3) << endl;
  std::cout << box1->intersects(*box2) << endl;
  std::cout << box1->contains(*v5) << endl;
  std::cout << box1->intersects(*box3) << endl;
}

// // TODO
// void sRender(std::vector<Entity> &entities) {
//   for (auto &e : entities) {
//     if (e.cTransform && e.cShape) { // TODO: bitset filter
//       e.cTransform->pos += e.cTransform->vel;
//       e.cShape->shape.setPosition(e.cTransform->pos);
//       window.draw(e.cShape->shape);
//     }
//   }
// };
//
// void sMovement(std::vector<Entity> &entities) {
//   for (auto &e : entities) {
//     if (e.cTransform) { // TODO: bitset filter
//       e.cTransform->pos += e.cTransform->vel;
//     }
//   }
// };
//
// // TODO - collisions
// void sPhysics(std::vector<Entity> &entities){};
//
// // TODO
// void spawnEnemy() {
//   auto e = entities.addEntity("enemy");
//   e->cTransform = std::make_shared<CTransform>(args);
//   e->cShape = std::make_shared<CShape>(args);
// }
//
// // TODO
// void collisions() {
//   for (auto b : entities.getEntities("bullet"))
//     for (auto e : entities.getEntities("enemy"))
//       if (Physics::CheckCollision(b, e))
//         b->destroy();
//   e->destroy();
// }
