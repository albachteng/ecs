#include "Entity.h"

Entity::Entity() {}
Entity::Entity(const std::string &tag, size_t id) : tag(tag), id(id) {}

void Entity::destroy() { alive = false; };
std::string Entity::getTag() { return tag; }
