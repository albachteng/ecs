#pragma once
#include "CShape.h"
#include <iostream>

CShape::CShape() {
  vertices = 3;
  radius = SIZE;
  shape = sf::CircleShape(SIZE, 3);
  shape.setFillColor(sf::Color(0, 0, 0));
  shape.setOutlineColor(sf::Color(255, 255, 255));
  shape.setOutlineThickness(5.0f);
  shape.setOrigin(SIZE, SIZE);
  std::cout << "default shape" << std::endl;
};

CShape::CShape(float radius, size_t vertices, const sf::Color &fill,
               const sf::Color &outline, float thickness)
    : vertices(vertices), radius(radius),
      shape(sf::CircleShape(radius, vertices)) {
  shape.setFillColor(fill);
  shape.setOutlineColor(outline);
  shape.setOutlineThickness(thickness);
  shape.setOrigin(radius, radius);
  std::cout << "shape with " << vertices << " vertices" << std::endl;
};

// sf::CircleShape CShape::getShape() { return shape; };
