#include <string>
class Entity {
  friend class EntityManager;
  size_t total = 0; // lifetime total, not current size
  const size_t id = 0;
  const std::string tag = "default"; // TODO, int
  bool alive = true;

public:
  Entity();
  Entity(const std::string &tag);
  std::string getTag();
};
