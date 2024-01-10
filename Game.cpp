#pragma once
#include "Game.h"
#include "Physics.h"
#include <cstdlib>
#include <iostream>
#include <memory>

Game::Game(const std::string &path) { init(path); }

void Game::init(const std::string &path) {
  // TODO: config
  // std::ifstream fin(path);
  // fin >> playerConfig.radius >> playerConfig.collisionradius >> etc

  srand(time(NULL));
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
      spawnBullet(player, mousePos);
      sEnemySpawner();
      sMovement();
      sCollision();
      sUserClearInput();
      sUserInput(event);
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

void Game::sMovement() {
  for (auto &e : entityManager.getEntities()) {
    if (e->cTransform) {
      e->cTransform->pos.x += e->cTransform->vel.x;
      e->cTransform->pos.y += e->cTransform->vel.y;
    }
    if (e->cTransform->pos.x >=
            window.getSize().x - e->cShape->shape.getRadius() ||
        e->cTransform->pos.x <= e->cShape->shape.getRadius()) {
      e->cTransform->vel.x *= -1;
    }
    if (e->cTransform->pos.y >=
            window.getSize().y - e->cShape->shape.getRadius() ||
        e->cTransform->pos.y <= e->cShape->shape.getRadius()) {
      e->cTransform->vel.y *= -1;
    }
  }
  if (player->cInput->left) {
    player->cTransform->vel.x -= .1f;
  }
  if (player->cInput->right) {
    player->cTransform->vel.x += .1f;
  }
  if (player->cInput->up) {
    player->cTransform->vel.y -= .1f;
  }
  if (player->cInput->down) {
    player->cTransform->vel.y += .1f;
  }
}

// TODO
void Game::sEnemySpawner() {
  if (currentFrame - lastEnemySpawn > 180) {

    lastEnemySpawn = currentFrame;
    float posX = rand() % window.getSize().x;
    float posY = rand() % window.getSize().y;
    float velX = rand() % 10;
    float velY = rand() % 10;
    int sides = rand() % 10;
    int R = rand() % 255;
    int G = rand() % 255;
    int B = rand() % 255;
    int angle = rand() % 360;
    auto e = entityManager.addEntity("enemy");
    e->cTransform =
        std::make_shared<CTransform>(Vec2(posX, posY), Vec2(velX, velY));
    e->cShape = std::make_shared<CShape>(50.0f, sides, sf::Color(R, G, B),
                                         sf::Color(255, 255, 255), 5.0f);
    e->cTransform->angle += angle;
  }
}

void Game::sUserInput(sf::Event) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    player->cInput->left = true;
    std::cout << "left" << std::endl;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    player->cInput->right = true;
    std::cout << "right" << std::endl;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    player->cInput->up = true;
    std::cout << "up" << std::endl;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    player->cInput->down = true;
    std::cout << "down" << std::endl;
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    player->cInput->shoot = true;
    std::cout << "shoot" << std::endl;
    mousePos = Vec2(sf::Mouse::getPosition(window).x,
                    sf::Mouse::getPosition(window).y);
    std::cout << "mouse pos: " << mousePos.x << ", " << mousePos.y << std::endl;
  }
}

void Game::sUserClearInput() {
  player->cInput->left = false;
  player->cInput->right = false;
  player->cInput->up = false;
  player->cInput->down = false;
  player->cInput->shoot = false;
}

void Game::spawnBullet(std::shared_ptr<Entity> p, const Vec2 &m) {
  if (currentFrame - lastBulletSpawn > 20 && p->cInput->shoot) {
    lastBulletSpawn = currentFrame;
    float x = m.x - p->cShape->shape.getPosition().x;
    float y = m.y - p->cShape->shape.getPosition().y;
    float c = sqrt(x * x + y * y);
    float posX = p->cShape->shape.getPosition().x;
    float posY = p->cShape->shape.getPosition().y;
    float velX = x / c * 10.0f;
    float velY = y / c * 10.0f;
    int sides = 10;
    int R = 255;
    int G = 255;
    int B = 255;
    auto e = entityManager.addEntity("bullet");
    e->cTransform =
        std::make_shared<CTransform>(Vec2(posX, posY), Vec2(velX, velY));
    e->cShape = std::make_shared<CShape>(5.0f, sides, sf::Color(R, G, B),
                                         sf::Color(0, 0, 255), 1.0f);
  }
};

void Game::sCollision() {
  // TODO - the same but with bullets instead
  for (auto e : entityManager.getEntities("enemy"))
    for (auto b : entityManager.getEntities("bullet"))
      if (Physics::isCollision(b, e)) {
        std::cout << "hit" << std::endl;
        e->destroy();
        b->destroy();
      }
}
