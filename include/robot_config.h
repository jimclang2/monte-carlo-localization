#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"         // IWYU pragma: keep
#include "pros/distance.hpp"


// Motor ports
constexpr int INTAKE_PORT = 21;
constexpr int OUTTAKE_PORT = 12;

// Declare all hardware (using extern so they're defined once in .cpp)
extern pros::Rotation rotation_sensor;
extern pros::Imu imu;
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern lemlib::Drivetrain drivetrain;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::OdomSensors sensors;
extern lemlib::Chassis chassis;

extern pros::Motor Intake;
extern pros::Motor Outtake;

extern pros::adi::DigitalOut Descore;
extern pros::adi::DigitalOut Unloader;
extern pros::adi::DigitalOut MidScoring;

extern pros::Controller master;

// Distance sensors for MCL
// TODO: Update ports when sensors are physically mounted on the robot
extern pros::Distance dNorth;
extern pros::Distance dSouth;
extern pros::Distance dEast;
extern pros::Distance dWest;

// Initialization function
void initializeRobot();
