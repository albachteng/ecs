#include "EntityManager.h"

class GameEngine {
  int currentFrame;
  EntityManager entityManager;

public:
  GameEngine();
  void mainLoop();
};
