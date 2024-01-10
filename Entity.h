#pragma once
#include "CBBox.cpp"
#include "CInput.h"
#include "CLifespan.h"
#include "CName.cpp"
#include "CShape.cpp"
#include "CTransform.cpp"
#include <memory>
#include <string>

class Entity {
  friend class EntityManager;
  size_t total = 0; // lifetime total, not current size
  const size_t id = 0;
  const std::string tag = "default"; // TODO, int

public:
  bool alive = true;
  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CName> cName;
  std::shared_ptr<CShape> cShape;
  std::shared_ptr<CBBox> cBBox;
  std::shared_ptr<CInput> cInput;
  std::shared_ptr<CLifespan> cLifespan;
  Entity();
  Entity(const std::string &tag, size_t id);
  std::string getTag();
  void destroy();
};
