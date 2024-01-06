#include "Terrain.hpp"
#include <cstddef>
#include <iostream>

// TODO
#define RAND 1

World::World(int width, int height)
    : width(width = WIDTH), height(height = HEIGHT), plain(1), hill(3),
      river(2) {
  tiles = new Terrain *[height];
  for (ptrdiff_t i = 0; i < height; i++) {
    tiles[i] = new Terrain[width];
    for (ptrdiff_t j = 0; j < width; j++) {
      tiles[i][j] = Terrain(RAND);
    }
  }
}

Terrain **World::getTiles() { return tiles; }
int World::getHeight() { return height; }
int World::getWidth() { return width; }

Terrain::Terrain() : move_cost(0){};
Terrain::Terrain(int move_cost) : move_cost(move_cost){};

int Terrain::getMoveCost() { return move_cost; }

void Terrain::printTerrain() {
  std::string name;
  switch (move_cost) {
  case 1: {
    name = "plains";
    break;
  }
  case 2: {
    name = "river";
    break;
  }
  case 3: {
    name = "hill";
    break;
  }
  default:
    name = "whoops";
    break;
  }
  std::cout << name << std::endl;
}

World::~World() {}
