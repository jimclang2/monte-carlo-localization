#include "robot_config.h"

// Vertical Tracking Wheel
pros::Rotation rotation_sensor(-11);

pros::Imu imu(13);

pros::MotorGroup left_motors({-20, -17, 18}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({19, 16, -15}, pros::MotorGearset::blue);

// drivetrain settings
lemlib::Drivetrain
    drivetrain(&left_motors,               // left motor group
               &right_motors,              // right motor group
               11.5,                       // 11.5 inch track width
               lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
               450,                        // drivetrain rpm is 450rpm
               5 // horizontal drift (omni + traction wheel mix)
    );

// tracking wheel configuration
lemlib::TrackingWheel vertical_tracking_wheel(&rotation_sensor,
                                              lemlib::Omniwheel::NEW_275, .375);
// vertical wheel, 2.75" diameter, .375" offset from tracking center

// odometry sensors configuration
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel
                            nullptr, // no second vertical wheel
                            nullptr, // no horizontal tracking wheel
                            nullptr, // no second horizontal wheel
                            &imu     // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(4.25, // kP
                                              0,    // kI
                                              1,    // kD
                                              3,    // anti windup
                                              1,    // small error range
                                              100,  // small error range timeout
                                              3,    // large error range
                                              500,  // large error range timeout
                                              0     // slew
);

// angular PID controller - TUNED
lemlib::ControllerSettings
    angular_controller(.863,  // kP
                       0,     // kI
                       0.235, // kD
                       3,     // anti windup
                       1,     // small error range, in degrees
                       100,   // small error range timeout
                       3,     // large error range, in degrees
                       500,   // large error range timeout
                       0      // slew
    );

// Drive curves
lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.05);
lemlib::ExpoDriveCurve steer_curve(3, 10, 1.05);

// create the chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        sensors, &throttle_curve, &steer_curve);

// --------------------- Motors ---------------------
pros::Motor Intake(INTAKE_PORT, pros::MotorGears::blue,
                   pros::MotorUnits::degrees);
pros::Motor Outtake(OUTTAKE_PORT, pros::MotorGears::blue,
                    pros::MotorUnits::degrees);

// --------------------- Pneumatics ---------------------
pros::adi::DigitalOut Descore('A');
pros::adi::DigitalOut Unloader('C');
pros::adi::DigitalOut MidScoring('B');

// --------------------- Controller ---------------------
pros::Controller master(pros::E_CONTROLLER_MASTER);

// --------------------- Distance Sensors (MCL) ---------------------
// TODO: Update ports when distance sensors are physically mounted on robot
// Mount sensors pointing N/S/E/W at field walls for best MCL performance
pros::Distance dNorth(1); // TODO: update port
pros::Distance dSouth(2); // TODO: update port
pros::Distance dEast(3);  // TODO: update port
pros::Distance dWest(4);  // TODO: update port

void initializeRobot() {
  // Non-blocking calibration - fixes "Run" mode hang
  chassis.calibrate(false);

  // Set brake modes
  left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  Outtake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  Intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  Outtake.set_reversed(false);
  Intake.set_reversed(true);
  MidScoring.set_value(false);
}
