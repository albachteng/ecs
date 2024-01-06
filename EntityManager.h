#include "Entity.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

// TODO remove shared_ptrs
typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager {
  friend class Entity;
  EntityVec entities;
  EntityVec toAdd;
  EntityMap entityMap;

public:
  EntityManager();
  void update();
  static std::shared_ptr<Entity> addEntity(const std::string &tag);
  EntityVec &getEntities();
  EntityVec &getEntities(const std::string &tag);
};
