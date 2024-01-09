// #include "CBBox.h"
#include "CShape.h"
// #include "Entity.cpp"
#include "Terrain.cpp"
#include "iostream"
#include <algorithm>
#include <ostream>

int main() { CShape *s = new CShape(); }

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
