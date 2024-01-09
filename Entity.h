#pragma once
#include "CBBox.cpp"
#include "CInput.h"
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
  bool alive = true;

public:
  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CName> cName;
  std::shared_ptr<CShape> cShape;
  std::shared_ptr<CBBox> cBBox;
  std::shared_ptr<CInput> cInput;
  Entity();
  Entity(const std::string &tag, size_t id);
  std::string getTag();
  void destroy();
};
