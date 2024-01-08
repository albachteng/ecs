#include "EntityManager.h"

void EntityManager::update() {
  for (auto &e : toAdd) {
    entities.push_back(e);
    entityMap[e->getTag()].push_back(e);
  }
  for (auto &e : entities) {
    // TODO: remove dead entities
    // std::remove_if
  }
  toAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
  // TODO: auto e = std::shared_ptr<Entity>(new Entity(tag, totalEntities++));
  auto e = std::make_shared<Entity>(tag, totalEntities++);
  toAdd.push_back(e);
  return e;
};

EntityVec &EntityManager::getEntities() { return entities; }

EntityVec &EntityManager::getEntities(const std::string &tag) {
  return entityMap[tag];
}
