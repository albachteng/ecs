#include "Entity.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager {
  EntityVec entities;
  EntityVec toAdd;
  EntityMap entityMap;
  size_t total = 0; // lifetime total, not current size
  const size_t id = 0;
  const std::string tag = "default"; // TODO, int
  bool alive = true;

public:
  EntityManager();
  void update();
  std::shared_ptr<Entity> addEntity(const std::string &tag);
  EntityVec &getEntities();
  EntityVec &getEntities(const std::string &tag);
};
