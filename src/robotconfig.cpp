#include "Solenoid.hpp"
#include "cata.hpp"
#include "graphy/Grapher.hpp"
#include "intake.h"
#include "lemlib/chassis/trackingWheel.hpp"
#include "lights.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include <iostream>
#include "lemlib/api.hpp"

sylib::Addrled underglowLED(22, 8, 28);
sylib::Addrled intakeLED(22, 9, 22);
sylib::Addrled rightDriveLED(22,6, 36);
sylib::Addrled leftDriveLED(22, 7, 36);

pros::Motor leftFront(20, true);
pros::Motor leftBack(18, true);
pros::Motor leftTop(19, false);

pros::Motor rightFront(11, false);
pros::Motor rightBack(12, false);
pros::Motor rightTop(14, true);

pros::Motor_Group leftMotors({leftFront, leftBack, leftTop});
pros::Motor_Group rightMotors({rightFront, rightBack, rightTop});

pros::Imu imu(13);
// drivetrain
lemlib::Drivetrain_t drivetrain {&leftMotors, &rightMotors, 10.375, lemlib::Omniwheel::NEW_325, 360, 13};

// lateral motion controller
lemlib::ChassisController_t lateralController {12, 30, 1, 100, 3, 500, 3};

// angular motion controller
lemlib::ChassisController_t angularController {2, 13.5, 1, 100, 3, 500, 20};

// sensors for odometry
pros::ADIEncoder enc('A', 'B');
lemlib::TrackingWheel tracking_wheel(&enc, 2.75, 0);
lemlib::OdomSensors_t sensors {&tracking_wheel, nullptr, nullptr, nullptr, &imu};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor cataMotor(10, false);

balls::Catapult catapult(cataMotor);

pros::Motor intakeMotor(9, true);

Intake intake(intakeMotor);

ryan::Solenoid blocker('D');

ryan::Solenoid Lwingus('C');
ryan::Solenoid Rwingus('E');

balls::Lights lights(underglowLED, intakeLED, leftDriveLED, rightDriveLED);