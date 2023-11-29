#include "lemlib/asset.hpp"
#include "pros/rtos.hpp"
#include "robotconfig.h"
#include <iostream>

ASSET(skillspush_txt)
ASSET(sidepush_txt)
ASSET(farSideMidRush_txt)
ASSET(farSideMidRushContact_txt)

#define RAM(left_speed, right_speed, duration)                                 \
  do {                                                                         \
    chassis.tank(left_speed, right_speed);                                     \
    pros::delay(duration);                                                     \
    chassis.tank(0, 0);                                                        \
  } while (0)

#define WAIT_UNTIL_DONE chassis.waitUntilDist(-1);

#define TOGGLE_WINGS                                                           \
  Lwingus.toggle();                                                            \
  Rwingus.toggle();

#define TurnToAngle(desiredTheta, timeout)                                     \
  chassis.moveTo(chassis.getPose().x, chassis.getPose().y, desiredTheta,       \
                 timeout);

void closeSide3() {
  chassis.setPose(-17, 59.5, 90);
  intake = Intake::STATE::IN;
  chassis.moveTo(-6, 59.5, 90, 1000);
  chassis.moveTo(-64, 20, 0, 2500, false, false, 13, .65, 110);
  chassis.setPose(-64, 29.625, 0);
  chassis.moveTo(-60, 34, 0, 1000);
  chassis.turnTo(chassis.getPose().x, -60, 500);
  intake = Intake::STATE::OUT;
  chassis.moveTo(chassis.getPose().x, 10, 180, 650);
  intake = Intake::STATE::IDLE;
  std::cout << chassis.getPose().x << " " << chassis.getPose().y << std::endl;
  chassis.moveTo(-50, 45, -135, 1000, false, false);
  intake = Intake::STATE::IN;
  chassis.moveTo(-6, 25, 90, 1500);
  chassis.moveTo(-10, 25, 90, 500, false, false);
  chassis.turnTo(-55, -50, 750);
  intake = Intake::STATE::HOLD;
  chassis.moveTo(-70, 7, -90, 1000);
  chassis.moveTo(-40, 7, -90, 1000, false, false);
}

void closeSideMid() { // this shawty does NOT work
  closeSide3();
}

void farSide() {
  chassis.setPose(-45, -54.25, 180);

  // aim to slap the triball out
  chassis.turnTo(-60, -70, 750);

  // slap the triball out
  Rwingus.toggle();
  pros::delay(500);

  chassis.turnTo(-30, -70, 750);
  Rwingus.toggle();

  // score preload in goal
  chassis.moveTo(-59, -12, 180, 1500, false, false, 0, 0.75);

  // move that jawn to the elevation bar and knock those triballs to the other
  // side
  chassis.moveTo(4, -57, 90, 3000, true, true, 0, 0.85);
  chassis.waitUntilDist(10);
  blocker.toggle();
  WAIT_UNTIL_DONE;
}

void farSideMid() {

  chassis.setPose(-40.75, -54.25, 180);

  // GAS GAS GAS !!!
  chassis.follow(farSideMidRush_txt, 5000, 12, true, false);
  chassis.waitUntilDist(45);
  TOGGLE_WINGS;
  WAIT_UNTIL_DONE;
  return;

  // score the baddie in the intake
  chassis.moveTo(-15, chassis.getPose().y, -90, 750);
  chassis.waitUntilDist(5);
  intake = Intake::STATE::OUT;
  WAIT_UNTIL_DONE;
  intake = Intake::STATE::IDLE;
  TurnToAngle(-90, 1000);
  chassis.moveTo(-50, chassis.getPose().y, -90, 1000, false, false);

  // try to descore the triball
  chassis.follow(farSideMidRushContact_txt, 7000, 8, true);
  chassis.waitUntilDist(82);
  Rwingus.toggle();
  chassis.waitUntilDist(100);
  Rwingus.toggle();
  chassis.waitUntilDist(120);
  blocker.toggle();
  WAIT_UNTIL_DONE;
}

void skills() {
  chassis.setPose(-40.5, 54.5, 90);

  // push preload into goal

  // move to matchloader
  chassis.moveTo(-62, 48, 105, 1500, false, false);
  Lwingus.toggle();

  /*
  // shoot matchloads
  catapult.setState(balls::Catapult::State::Matchload);

  while (catapult.getState() == balls::Catapult::State::Matchload) {
    pros::delay(20);
  }
  */
  pros::delay(1000);
  Lwingus.toggle();
  // push time !!
  TurnToAngle(-90, 1000);
  chassis.follow(skillspush_txt, 7000, 17, true, false, 90);
  chassis.waitUntilDist(115);
  TOGGLE_WINGS;
  WAIT_UNTIL_DONE;
}