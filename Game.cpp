#pragma once
#include "Game.h"
#include "CScore.h"
#include "Physics.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#define DFT_WIN_W 1280
#define DFT_WIN_H 720
#define DFT_FRAMERATE 60
#define DFT_PAUSE_THROTTLE 5

#define DFT_EN_SPAWNRATE 180

#define DFT_SM_EN_RESIZE 2.5f
#define DFT_SM_EN_OUTLINE 1.0f
#define DFT_SM_EN_TTL 180

#define DAMPING 0.95f

#define WHITE sf::Color(255, 255, 255)

void Game::setFont(const std::string &path) { font.loadFromFile(path); }
Game::Game(const std::string &path) { init(path); }

void Game::init(const std::string &path) {
  // TODO: config
  std::ifstream fin(path);
  fin >> playerConfig.velX >> playerConfig.velY >> playerConfig.radius >>
      playerConfig.outline >> playerConfig.R >> playerConfig.G >>
      playerConfig.B >> playerConfig.r >> playerConfig.g >> playerConfig.b >>
      enemyConfig.radius >> enemyConfig.outline >> enemyConfig.spawnate >>
      enemyConfig.maxVel >> enemyConfig.minVel >> enemyConfig.maxSides >>
      enemyConfig.minSides >> bulletConfig.throttle >> bulletConfig.sides >>
      bulletConfig.ttl >> bulletConfig.R >> bulletConfig.G >> bulletConfig.B >>
      bulletConfig.vel >> bulletConfig.outline;
  std::cout << "XXX" << playerConfig.velX;
  std::cout << playerConfig.velY;

  srand(time(NULL));
  // TODO read in from config file, fullscreen/windows
  window.create(sf::VideoMode(DFT_WIN_W, DFT_WIN_H), "game thang");
  window.setFramerateLimit(DFT_FRAMERATE);
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(WHITE);
  text.setPosition(0, 0);
  spawnPlayer();
}

void Game::run() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
  while (running) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
      setPaused(!paused);
    }
    entityManager.update();
    std::cout << "size: " << entityManager.getEntities("small enemy").size()
              << std::endl;
    if (!paused) {
      spawnBullet(player, mousePos);
      sLifespan();
      sEnemySpawner();
      sMovement();
      sCollision();
      sUserClearInput();
      sUserInput();
    }
    sRender();
    currentFrame++;
  }
}

void Game::setPaused(bool p) {
  // eagerly pause, but don't unpause if they just hit P
  if (currentFrame - lastPaused < DFT_PAUSE_THROTTLE)
    paused = p;
  lastPaused = currentFrame;
};

void Game::spawnPlayer() {
  auto entity = entityManager.addEntity("player");
  entity->cTransform = std::make_shared<CTransform>(
      Vec2(window.getSize().x / 2, window.getSize().y / 2),
      Vec2(playerConfig.velX, playerConfig.velY) /*  DFT_PL_VEL */);
  // TODO shape, input, etc
  entity->cShape = std::make_shared<CShape>(
      playerConfig.radius, 8,
      sf::Color(playerConfig.R, playerConfig.G, playerConfig.B),
      sf::Color(playerConfig.r, playerConfig.g, playerConfig.b),
      playerConfig.outline);
  // DFT_PL_RAD, 8, DFT_PL_COLOR, DFT_PL_OUTLINE_COLOR, DFT_PL_OUTLINE);
  entity->cInput = std::make_shared<CInput>();
  player = entity;
}

void Game::sRender() {
  window.clear();
  text.setString(std::to_string(score));
  for (auto &e : entityManager.getEntities()) {
    if (e->cShape && e->cTransform) {
      e->cShape->shape.setPosition(e->cTransform->pos.X(),
                                   e->cTransform->pos.Y());
      e->cTransform->angle += 1.0f;
      e->cShape->shape.setRotation(e->cTransform->angle);
      window.draw(e->cShape->shape);
    }
  }
  window.draw(text);
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
      e->cTransform->vel.x *= -DAMPING;
    }
    if (e->cTransform->pos.y >=
            window.getSize().y - e->cShape->shape.getRadius() ||
        e->cTransform->pos.y <= e->cShape->shape.getRadius()) {
      e->cTransform->vel.y *= -DAMPING;
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
  if (currentFrame - lastEnemySpawn > DFT_EN_SPAWNRATE) {

    lastEnemySpawn = currentFrame;
    float posX = rand() % window.getSize().x;
    float posY = rand() % window.getSize().y;
    float velX = rand() % enemyConfig.maxVel + enemyConfig.minVel;
    float velY = rand() % enemyConfig.maxVel + enemyConfig.minVel;
    int sides = rand() % (enemyConfig.maxSides - enemyConfig.minSides) +
                enemyConfig.minSides;
    int R = rand() % 255;
    int G = rand() % 255;
    int B = rand() % 255;
    int angle = rand() % 360;
    auto e = entityManager.addEntity("enemy");
    e->cTransform =
        std::make_shared<CTransform>(Vec2(posX, posY), Vec2(velX, velY));
    e->cShape =
        std::make_shared<CShape>(enemyConfig.radius, sides, sf::Color(R, G, B),
                                 WHITE, enemyConfig.outline);
    e->cTransform->angle += angle;
    e->cScore = std::make_shared<CScore>(50);
  }
}

// TODO if (even.type == sf::Event::KeyPressed) {switch event.key.code...} etc
// else if (event.type == sf::eEvent::KeyReleased) switch...
void Game::sUserInput() {
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
    // std::cout << "shoot" << std::endl;
    mousePos = Vec2(sf::Mouse::getPosition(window).x,
                    sf::Mouse::getPosition(window).y);
    // std::cout << "mouse pos: " << mousePos.x << ", " << mousePos.y <<
    // std::endl;
  }
  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
  //   setPaused(!paused);
  //   std::cout << "paused: " << paused << std::endl;
  // }
}

void Game::sUserClearInput() {
  player->cInput->left = false;
  player->cInput->right = false;
  player->cInput->up = false;
  player->cInput->down = false;
  player->cInput->shoot = false;
}

void Game::spawnBullet(std::shared_ptr<Entity> p, const Vec2 &m) {
  if (currentFrame - lastBulletSpawn > bulletConfig.throttle &&
      p->cInput->shoot) {
    lastBulletSpawn = currentFrame;
    float x = m.x - p->cShape->shape.getPosition().x;
    float y = m.y - p->cShape->shape.getPosition().y;
    float c = sqrt(x * x + y * y);
    float posX = p->cShape->shape.getPosition().x;
    float posY = p->cShape->shape.getPosition().y;
    float velX = x / c * bulletConfig.vel;
    float velY = y / c * bulletConfig.vel;
    int sides = bulletConfig.sides;
    auto e = entityManager.addEntity("bullet");
    e->cTransform =
        std::make_shared<CTransform>(Vec2(posX, posY), Vec2(velX, velY));
    e->cShape = std::make_shared<CShape>(
        5.0f, sides, WHITE,
        sf::Color(bulletConfig.R, bulletConfig.G, bulletConfig.B),
        bulletConfig.outline);
    e->cLifespan = std::make_shared<CLifespan>(currentFrame, bulletConfig.ttl);
  }
};

void Game::sCollision() {
  for (auto b : entityManager.getEntities("bullet")) {
    for (auto e : entityManager.getEntities("small enemy")) {
      if (Physics::isCollision(b, e)) {
        std::cout << "hit" << std::endl;
        // spawnSmallEnemies(e);
        e->destroy();
        b->destroy();
        score += e->cScore->score;
      }
    }
    for (auto e : entityManager.getEntities("enemy")) {
      if (Physics::isCollision(b, e)) {
        std::cout << "hit" << std::endl;
        spawnSmallEnemies(e);
        e->destroy();
        b->destroy();
        score += e->cScore->score;
      }
    }
  }
  for (ptrdiff_t i = 0; i < entityManager.getEntities("enemy").size(); i++) {
    for (ptrdiff_t j = i + 1; j < entityManager.getEntities("enemy").size();
         j++) {
      auto &first = entityManager.getEntities("enemy")[i];
      auto &second = entityManager.getEntities("enemy")[j];
      if (Physics::isCollision(first, second)) {
        // they should bounce off of one-another
        // first->cTransform->vel -= (second->cTransform->vel * DAMPING);
        // second->cTransform->vel -= (first->cTransform->vel * DAMPING);
        first->cTransform->vel *= -DAMPING;
        second->cTransform->vel *= -DAMPING;
      }
    }
  }
}

std::vector<std::pair<float, float>> generateVelocityVectors(int numVertices,
                                                             int angleOffset) {
  // Calculate the angle between each pair of consecutive vectors
  float angleIncrement = 2 * M_PI / numVertices;

  // Generate velocity vectors
  std::vector<std::pair<float, float>> velocityVectors;
  for (int i = 0; i < numVertices; ++i) {
    float angle = (i * angleIncrement) + angleOffset;
    float x = std::cos(angle);
    float y = std::sin(angle);
    velocityVectors.push_back({x, y});
  }

  return velocityVectors;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e) {
  std::cout << "small enemy with " << e->cShape->vertices << " sides"
            << std::endl;
  std::vector<std::pair<float, float>> vecs =
      generateVelocityVectors(e->cShape->vertices, e->cTransform->angle);
  for (auto &p : vecs) {
    std::cout << p.first << " " << p.second << std::endl;
    auto s = entityManager.addEntity("small enemy");
    s->cShape = std::make_shared<CShape>(
        e->cShape->radius / DFT_SM_EN_RESIZE, e->cShape->vertices,
        e->cShape->shape.getFillColor(), WHITE, DFT_SM_EN_OUTLINE);
    s->cTransform = std::make_shared<CTransform>(e->cTransform->pos,
                                                 Vec2(p.first, p.second));
    s->cLifespan = std::make_shared<CLifespan>(currentFrame, DFT_SM_EN_TTL);
    s->cScore = std::make_shared<CScore>(100);
  }
}

void Game::sLifespan() {
  for (auto e : entityManager.getEntities()) {
    if (e->cLifespan) {
      if (currentFrame - e->cLifespan->start >= e->cLifespan->ttl) {
        e->destroy();
      }
    }
  }
}
