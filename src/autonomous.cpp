#include "autonomous.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/rtos.hpp"
#include "robot/monte.hpp"
#include "robot_config.h"


// =============================================================================
// Skills Autonomous
// =============================================================================
// MCL can be enabled here for long skills runs to correct odometry drift.
// Toggle useNorthSensor / useSouthSensor / useEastSensor / useWestSensor
// before/after moves near Goals to avoid bad sensor readings.
// =============================================================================

void skills_auton() {
  // Uncomment to enable MCL drift correction (requires distance sensors):
  // startMCL(chassis);

  chassis.setPose(0, 0, 270);
  chassis.moveToPoint(-32.5, 5, 1550);
  chassis.turnToHeading(180, 800, {}, false);
  Unloader.set_value(true);
  Intake.move(-127);
  pros::delay(500);
  chassis.moveToPoint(-32.5, -15, 700, {.maxSpeed = 100}); // unload
  pros::delay(2100);
  chassis.moveToPoint(-32.5, 5, 1550, {.forwards = false, .maxSpeed = 80},
                      false);
  Unloader.set_value(false);
  Intake.move(0);
  chassis.turnToHeading(90, 800);
  chassis.moveToPoint(-55, 5, 800, {.forwards = false, .minSpeed = 50},
                      false); // allign
  chassis.setPose(0, 0, 90);

  chassis.turnToHeading(0, 800);
  chassis.moveToPoint(0, 93, 1800, {.maxSpeed = 80});
  chassis.turnToHeading(90, 800);
  chassis.moveToPoint(-60, 93, 800, {.forwards = false, .minSpeed = 60},
                      false); // allign

  chassis.setPose(0, 0, 90);
  chassis.moveToPoint(17, 0, 900);
  chassis.turnToHeading(0, 800);
  chassis.moveToPoint(17, -20, 1100, {.forwards = false},
                      false); // go back to goal
  Outtake.move(127);
  Intake.move(-127);
  Unloader.set_value(true);
  pros::delay(2000);
  left_motors.move(40);
  right_motors.move(40);
  pros::delay(75);
  left_motors.brake();
  right_motors.brake();
  chassis.turnToHeading(0, 500);
  Outtake.move(-30);
  chassis.moveToPoint(19, 40, 1100, {.maxSpeed = 60}); // unload
  pros::delay(2300);

  chassis.moveToPose(16.5, -10, 0, 1400, {.forwards = false, .minSpeed = 60},
                     false); // go back to goal
  chassis.turnToHeading(0, 750);
  chassis.moveToPoint(16.5, -60, 900, {.forwards = false, .maxSpeed = 75},
                      false); // go back to goal
  Outtake.move(127);
  Unloader.set_value(false);
  pros::delay(2000);
  chassis.moveToPoint(16, -3, 1000);
  Outtake.move(0);
  Intake.move(0);
  chassis.turnToHeading(270, 800);
  chassis.moveToPose(115, -3, 270, 2750, {.forwards = false});
  chassis.moveToPose(150, -3, 270, 1200, {.forwards = false, .maxSpeed = 50},
                     false);

  chassis.setPose(0, 0, 270);
  chassis.moveToPoint(-19, 0, 1000);
  chassis.turnToHeading(0, 800, {}, false);
  Unloader.set_value(true);
  Intake.move(-127);
  pros::delay(500);
  chassis.moveToPoint(-19, 200, 600, {.maxSpeed = 70}); // unload
  pros::delay(2400);
  chassis.moveToPoint(-19, -5, 1000, {.forwards = false}, false);
  Unloader.set_value(false);
  Intake.move(0);
  chassis.turnToHeading(270, 800);
  chassis.moveToPoint(100, -5, 1000, {.forwards = false, .maxSpeed = 60},
                      false);
  chassis.setPose(0, 0, 270);
  chassis.swingToHeading(0, lemlib::DriveSide::RIGHT, 800, {}, false); // turn
  chassis.moveToPose(1, -95, 0, 2500, {.forwards = false});
  chassis.turnToHeading(270, 800);
  chassis.moveToPoint(1000, -90, 800, {.forwards = false, .maxSpeed = 60},
                      false);
  chassis.setPose(0, 0, 270);
  chassis.moveToPoint(-17, 0, 1000);
  chassis.turnToHeading(180, 800);
  chassis.moveToPoint(-17, 30, 1250, {.forwards = false, .maxSpeed = 80},
                      false);
  Outtake.move(127);
  Intake.move(-127);
  Unloader.set_value(true);
  pros::delay(2000);
  Outtake.move(-30);

  chassis.turnToHeading(180, 500);
  Outtake.move(-30);
  chassis.moveToPoint(-17, -40, 1250, {.maxSpeed = 60}); // unload
  pros::delay(2300);

  chassis.moveToPoint(-17, 0, 1400, {.forwards = false, .minSpeed = 60},
                      false); // go back to goal
  chassis.turnToHeading(180, 750);
  chassis.moveToPose(-17, 60, 180, 1100, {.forwards = false, .maxSpeed = 70},
                     false); // go back to goal
  Outtake.move(127);
  Unloader.set_value(false);
  pros::delay(2300);
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, 15, 1000);
  chassis.moveToPoint(15, 15, 1000);
  chassis.turnToHeading(180, 1000);
  chassis.moveToPoint(15, 60, 1500, {.forwards = false, .maxSpeed = 70}, false);
  chassis.setPose(0, 0, 0);
  chassis.turnToHeading(270, 1000, {}, false);
  chassis.moveToPoint(-25, -5, 1300, {.minSpeed = 100});

  // Uncomment to stop MCL at end of skills:
  // stopMCL();
}

// =============================================================================
// Match Autonomous Routines
// =============================================================================

void leftAuton_descore() { // 7 ball
  chassis.setPose(0, 0, 0);
  Descore.set_value(true);
  Intake.move(-127);
  chassis.moveToPoint(-10, 20, 2500);
  chassis.moveToPoint(-30, 0, 2000, {}, false);
  chassis.turnToPoint(-30, -10, 800);
  Unloader.set_value(true);
  pros::delay(300);
  chassis.moveToPoint(-30, -30, 800, {.maxSpeed = 70}, false); // unload
  pros::delay(400);
  Intake.move(0);
  chassis.moveToPoint(-30, 30, 1500, {.forwards = false, .maxSpeed = 80},
                      false);
  Intake.move(-127);
  Outtake.move(127);
  Unloader.set_value(false);
  Descore.set_value(false);
  pros::delay(2500);
  Intake.move(0);
  Outtake.move(0);
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, 12, 800);
  chassis.turnToHeading(90, 800);
  chassis.moveToPoint(-7, 12, 800, {.forwards = false, .minSpeed = 50}, false);
  chassis.turnToHeading(0, 750, {}, false);
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, -30, 9500, {.forwards = false});
}

void leftAuton() { // mid
  chassis.setPose(0, 0, 0);
  Descore.set_value(true);
  Intake.move(-127);
  chassis.moveToPoint(-10, 20, 2500);
  chassis.turnToPoint(8, 38, 1000, {.forwards = false});
  chassis.moveToPoint(8, 38, 2000, {.forwards = false, .maxSpeed = 80}, false);
  Intake.move(127);
  pros::delay(200);
  Intake.move(-127);
  Outtake.move(-127);
  MidScoring.set_value(true); // score mid
  pros::delay(2000);
  Outtake.move(0);
  MidScoring.set_value(false);
  chassis.moveToPoint(-35, 10, 2000, {}, false); // go to unload plane
  chassis.turnToHeading(183, 1000, {}, false);
  Unloader.set_value(true);
  pros::delay(500);
  chassis.moveToPoint(-32, -30, 800, {.maxSpeed = 70}, false); // unload
  pros::delay(500);
  Intake.move(0);
  chassis.moveToPoint(-32, 30, 2000, {.forwards = false, .maxSpeed = 80},
                      false);
  Intake.move(-127);
  Outtake.move(127);
  Unloader.set_value(false);
  Descore.set_value(false);
  pros::delay(2500);
  Intake.move(0);
  Outtake.move(0);
  left_motors.move(40);
  right_motors.move(40);
  pros::delay(200);
  left_motors.brake();
  right_motors.brake();
  pros::delay(300);
  chassis.swingToHeading(330, lemlib::DriveSide::RIGHT, 2000, {.minSpeed = 50});
  chassis.swingToHeading(15, lemlib::DriveSide::RIGHT, 1000, {}, false);
  pros::delay(300);
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, 16.7, 1000, {.minSpeed = 50});
}

void rightAuton() {
  chassis.setPose(0, 0, 0);
  Descore.set_value(true);
  Intake.move(-127);
  chassis.moveToPoint(10, 20, 2500);
  chassis.moveToPoint(30, 0, 2000, {}, false);
  chassis.turnToPoint(30, -10, 800);
  Unloader.set_value(true);
  pros::delay(300);
  chassis.moveToPoint(30, -30, 800, {.maxSpeed = 70}, false); // unload
  pros::delay(400);
  Intake.move(0);
  chassis.moveToPoint(30, 30, 1500, {.forwards = false, .maxSpeed = 80}, false);
  Intake.move(-127);
  Outtake.move(127);
  Unloader.set_value(false);
  Descore.set_value(false);
  pros::delay(2500);
  Intake.move(0);
  Outtake.move(0);
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, 12, 800);
  chassis.turnToHeading(90, 800);
  chassis.moveToPoint(-7, 12, 800, {.forwards = false, .minSpeed = 50}, false);
  chassis.turnToHeading(0, 750, {}, false);
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, -30, 9500, {.forwards = false});
}
