#include "TaskWrapper.hpp"
#include "main.h"

class Intake {

public:
  enum class STATE { IN, HOLD, OUT, IDLE };

private:
  STATE state = STATE::IDLE;
  pros::Motor &intakeMotor;

public:
  Intake(pros::Motor &intakeMotor) : intakeMotor(intakeMotor) {}

  STATE getState();
  void toggleTo(STATE newState);
  void update();
  void operator=(STATE newState);
};