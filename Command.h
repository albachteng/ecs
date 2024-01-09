#pragma once
#include "Entity.h"

class Command {
public:
  virtual ~Command() {}
  virtual void execute(Entity &actor);
};

void *jump();
void *shoot();

class JumpCommand : public Command {
public:
  virtual void execute(Entity &actor) { actor.jump(); };
};

class ShootCommand : public Command {
public:
  virtual void execute() { shoot(); };
};

class InputHandler {
public:
  void handleInput();
  // methods to bind commands...
private:
  Command *buttonX_;
  Command *buttonY_;
  Command *buttonA_;
  Command *buttonB_;
};
