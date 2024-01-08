#include <SFML/Graphics/CircleShape.hpp>
#include <cstddef>
#define SIZE 50.0f;

class CShape {
  size_t vertices = 3;
  CShape();
  CShape(size_t vertices);

public:
  sf::CircleShape shape = sf::CircleShape(SIZE, vertices);
  int getVertices();
};
