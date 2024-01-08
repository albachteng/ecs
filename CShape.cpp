#include "CShape.h"
#include <iostream>

CShape::CShape() { std::cout << "default shape" << std::endl; };

CShape::CShape(size_t vertices)
    : vertices(vertices), shape(sf::CircleShape(SIZE, vertices)) {
  std::cout << "shape with " << vertices << " vertices" << std::endl;
};
