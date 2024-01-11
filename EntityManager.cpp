#include "EntityManager.h"
#include <__algorithm/remove_if.h>

EntityManager::EntityManager(){};

bool isDead(std::shared_ptr<Entity> e) { return !e->alive; }

void EntityManager::update() {
  entities.erase(std::remove_if(entities.begin(), entities.end(), isDead),
                 entities.end());
  entityMap["bullet"].erase(std::remove_if(entityMap["bullet"].begin(),
                                           entityMap["bullet"].end(), isDead),
                            entityMap["bullet"].end());
  entityMap["enemy"].erase(std::remove_if(entityMap["enemy"].begin(),
                                          entityMap["enemy"].end(), isDead),
                           entityMap["enemy"].end());
  entityMap["small enemy"].erase(
      std::remove_if(entityMap["small enemy"].begin(),
                     entityMap["small enemy"].end(), isDead),
      entityMap["small enemy"].end());
  for (auto &e : toAdd) {
    entities.push_back(e);
    entityMap[e->getTag()].push_back(e);
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

size_t EntityManager::getTotal() { return totalEntities; };
