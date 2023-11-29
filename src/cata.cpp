#include "cata.hpp"
#include "autoSelect/selection.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "robotconfig.h"
#include <atomic>
#include <cmath>
#include <iostream>
#include <ostream>

using namespace balls;

void Catapult::loop() {

  int matchloadCount = 0;
  bool cataFireState = true;
  cataMotor.set_gearing(pros::E_MOTOR_GEARSET_36);

  while (true) {
    switch (cataState) {
    
    case State::Matchload:
      cataMotor.move_velocity(75);      

      if (cataFireState && cataMotor.get_efficiency() > 25) {
        cataFireState = false;
      }
      if (!cataFireState && cataMotor.get_efficiency() < 10) {
        cataFireState = true;
        matchloadCount++;
        if (matchloadCount >= 44) {
          leftDriveLED.set_all(0x990000);
          rightDriveLED.set_all(0x990000);
        }
        if (matchloadCount >= 46) {
          cataState = State::Idle;
          lights.setColor(selector::auton);
          continue;
        }
      }
      break;

    case State::Idle:
      cataMotor.move(0);
      break;

    case State::Firing:
      cataMotor.move_velocity(75);      
      break;
    }

    pros::delay(15);

  }
}

void Catapult::setState(Catapult::State newState) {cataState = newState;};

Catapult::State Catapult::getState() { return cataState; };