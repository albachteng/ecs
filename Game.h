#pragma once
#include "EntityManager.cpp"
#include <SFML/Graphics.hpp>
#include <memory>

struct BulletConfig {};
struct EnemyConfig {};
struct PlayerConfig {};

class Game {
  EntityManager entityManager;
  sf::RenderWindow window;
  sf::Font font;
  sf::Text text;
  PlayerConfig playerConfig;
  EnemyConfig enemyConfig;
  BulletConfig bulletConfig;
  int score = 0;
  int currentFrame = 0;
  int lastEnemySpawn = 0;
  bool paused = false;
  bool running = true;
  std::shared_ptr<Entity> player;

  void init(const std::string &configPath);
  void setPaused(bool paused);

  // Systems
  void sMovement(); // position, velocity, angle
  void sUserInput();
  void sLifespan();
  void sRender();
  void sEnemySpawner();
  void sCollision();

  void spawnPlayer();
  void spawnEnemy();
  void spawnSmallEnemies(std::shared_ptr<Entity> entity);
  void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos);
  void spawnSpecial(std::shared_ptr<Entity> entity);

public:
  Game(const std::string &path);
  void run();
};
