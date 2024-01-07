#include "EntityManager.h"

void EntityManager::update() {
  for (auto &e : toAdd) {
    entities.push_back(e);
    entityMap[e->getTag()].push_back(e);
  }
  for (auto &e : entities) {
    // TODO: remove dead entities
  }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
  auto e = std::make_shared<Entity>(tag, totalEntities++);
  toAdd.push_back(e);
  return e;
};

EntityVec &EntityManager::getEntities() { return this->entities; }

EntityVec &EntityManager::getEntities(const std::string &tag) {
  return this->entityMap[tag];
}
