#define WIDTH 10
#define HEIGHT 10

class Terrain {
public:
  Terrain(int move_cost) : move_cost(move_cost){};
  Terrain[]();
  int getMoveCost();

private:
  int move_cost;
  // TODO other intrinsic values
};

class World {
public:
  World(int width = WIDTH, int height = HEIGHT);
  void generateWorld();

private:
  // TODO
  int width;
  int height;
  Terrain plain;
  Terrain hill;
  Terrain river;
  Terrain **tiles;
};
