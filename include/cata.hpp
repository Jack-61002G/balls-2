#pragma once
#include "main.h"
#include "pros/rotation.hpp"
#include "taskwrapper.hpp"
#include <memory>
namespace balls {
class Catapult : public ryan::TaskWrapper {

public:
  enum class State { Idle, Firing, Matchload};

private:
  State cataState;
  pros::Motor &cataMotor;

public:
  Catapult(pros::Motor &cataMotor)
    : cataMotor(cataMotor) 
    {
      cataMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      cataState = State::Idle;
    }

  void loop() override;

  void setState(Catapult::State newState);

  Catapult::State getState();
  
};
} // namespace balls