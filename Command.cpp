#include "Command.h"

#define BUTTON_X 0
#define BUTTON_Y 0
#define BUTTON_A 0
#define BUTTON_B 0

int isPressed(char ch);

void InputHandler::handleInput() {
  if (isPressed(BUTTON_X))
    buttonX_->execute();
  else if (isPressed(BUTTON_Y))
    buttonY_->execute();
  else if (isPressed(BUTTON_A))
    buttonA_->execute();
  else if (isPressed(BUTTON_B))
    buttonA_->execute();
}
