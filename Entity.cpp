#include "Entity.h"

Entity::Entity() {}
Entity::Entity(const std::string &tag, size_t id) : tag(tag), id(id) {}

std::string Entity::getTag() { return this->tag; }
