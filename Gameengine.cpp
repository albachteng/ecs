#include "GameEngine.h"

void GameEngine::mainLoop() {
  entityManager.update();
  sUserInput();
  sMovement();
  sCollision();
  sRender();
  currentFrame++;
}

void GameEngine::sEnemySpawner() { auto e = entityManager.addEntity(args); }
