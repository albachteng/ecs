#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cstddef>

#define SIZE 50.0f

class CShape {
public:
  size_t vertices;
  sf::CircleShape shape;
  CShape(); // default shape
  CShape(float radius, size_t vertices, const sf::Color &fill,
         const sf::Color &outline, float thickness);
};
