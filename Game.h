#pragma once
#include "EntityManager.cpp"
#include <SFML/Graphics.hpp>
#include <memory>

typedef struct BulletConfig {
  int throttle, sides, ttl, R, G, B;
  float vel, outline;
} BulletConfig;

typedef struct EnemyConfig {
  float radius, outline;
  int spawnate, maxVel, minVel, maxSides, minSides;
} EnemyConfig;

typedef struct PlayerConfig {
  float velX, velY, radius, outline;
  int R, G, B, r, g, b;
} PlayerConfig;

class Game {
  EntityManager entityManager;
  sf::RenderWindow window;
  sf::Font font;
  sf::Text text;
  PlayerConfig playerConfig;
  EnemyConfig enemyConfig;
  BulletConfig bulletConfig;
  Vec2 mousePos;
  int score = 0;
  int currentFrame = 0;
  int lastEnemySpawn = 0;
  int lastBulletSpawn = 0;
  int lastPaused = 0;
  bool paused = false;
  bool running = true;
  std::shared_ptr<Entity> player;

  void init(const std::string &configPath);
  void setPaused(bool paused);

  // Systems
  void sMovement(); // position, velocity, angle
  void sUserInput();
  void sUserClearInput();
  void sLifespan();
  void sRender();
  void sEnemySpawner();
  void sCollision();

  void spawnPlayer();
  void spawnSmallEnemies(std::shared_ptr<Entity> entity);
  void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos);
  void spawnSpecial(std::shared_ptr<Entity> entity);

public:
  Game(const std::string &path);
  void run();
  void setFont(const std::string &path);
};
