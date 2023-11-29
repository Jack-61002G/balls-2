#pragma once
#include "Solenoid.hpp"
#include "cata.hpp"
#include "graphy/Grapher.hpp"
#include "intake.h"
#include "lemlib/chassis/chassis.hpp"
#include "lights.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"


extern lemlib::Chassis chassis;
extern pros::Controller controller;
extern pros::Motor cataMotor;
extern balls::Catapult catapult;
extern Intake intake;
extern sylib::Addrled intakeLED;
extern sylib::Addrled underglowLED;
extern sylib::Addrled rightDriveLED;
extern sylib::Addrled leftDriveLED;
extern ryan::Solenoid blocker;

extern pros::ADIEncoder enc;
extern lemlib::TrackingWheel tracking_wheel;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

extern ryan::Solenoid hang;
extern ryan::Solenoid Rwingus;
extern ryan::Solenoid Lwingus;

extern std::shared_ptr<graphy::AsyncGrapher> velocityTime;

extern balls::Lights lights;