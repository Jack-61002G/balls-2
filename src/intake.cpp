#include "intake.h"
#include "main.h"

Intake::STATE Intake::getState() { return this->state; }

void Intake::toggleTo(STATE newState) {
  if (state != STATE::IDLE) {
    state = STATE::IDLE;
    update();
  } else {
    state = newState;
    update();
}}

void Intake::update() {
  switch (state) {
  case STATE::IN:
    intakeMotor.move(127);
    break;
  case STATE::HOLD:
    intakeMotor.move_velocity(60);
    break;
  case STATE::OUT:
    intakeMotor.move(-127);
    break;
  case STATE::IDLE:
    intakeMotor.move_velocity(0);
    break;
}}

void Intake::operator=(STATE newState) { 
  if (state != newState) { 
    state = newState; 
    update(); 
}}

