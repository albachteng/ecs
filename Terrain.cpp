#include "Terrain.h"
#include <cstddef>

#define RAND 1

World::World(int width, int height)
    : width(width = WIDTH), height(height = HEIGHT), plain(1), hill(3),
      river(2) {
  tiles = new Terrain *[height];
  for (ptrdiff_t i = 0; i < height; i++) {
    tiles[i] = &(new Terrain(RAND))[width];
  }
}
