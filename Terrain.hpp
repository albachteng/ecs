#pragma once
#define WIDTH 10
#define HEIGHT 10

class Terrain {
public:
  Terrain();
  Terrain(int move_cost);
  int getMoveCost();
  void printTerrain();

private:
  int move_cost;
  // TODO other intrinsic values
};

class World {
public:
  World(int width = WIDTH, int height = HEIGHT);
  ~World();
  void generateWorld();
  int getHeight();
  int getWidth();
  Terrain **getTiles();

private:
  // TODO
  int width;
  int height;
  Terrain plain;
  Terrain hill;
  Terrain river;
  Terrain **tiles;
};
