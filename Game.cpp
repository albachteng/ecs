#include "Game.h"
#include <iostream>

Game::Game(const std::string &path) { init(path); }

void Game::init(const std::string &path) {
  // TODO: config
  // std::ifstream fin(path);
  // fin >> playerConfig.radius >> playerConfig.collisionradius >> etc

  // TODO read in from config file, fullscreen/windows
  window.create(sf::VideoMode(1280, 720), "game thang");
  window.setFramerateLimit(60);
  spawnPlayer();
}

void Game::run() {
  // TODO paused?
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
  std::cout << window.isOpen();
  while (running) {
    entityManager.update();
    if (!paused) {
      // sEnemySpawner();
      // sMovement();
      // sCollision();
      // sUserInput();
    }
    sRender();
    currentFrame++;
  }
}

void Game::setPaused(bool paused) { paused = paused; };

void Game::spawnPlayer() {
  auto entity = entityManager.addEntity("player");
  entity->cTransform =
      std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f));
  // TODO shape, input, etc
  entity->cShape = std::make_shared<CShape>(50.0f, 8, sf::Color(0, 0, 0),
                                            sf::Color(255, 0, 0), 5.0f);
  entity->cInput = std::make_shared<CInput>();
  player = entity;
}

void Game::sRender() {
  window.clear();
  for (auto &e : entityManager.getEntities()) {
    if (e->cShape && e->cTransform) {
      e->cShape->shape.setPosition(e->cTransform->pos.X(),
                                   e->cTransform->pos.Y());
      e->cTransform->angle += 1.0f;
      e->cShape->shape.setRotation(e->cTransform->angle);
      window.draw(e->cShape->shape);
    }
  }
  window.display();
}

// TODO
// void Game::sEnemySpawner() { auto e = entityManager.addEntity(args); }
