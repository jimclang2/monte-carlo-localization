#include "subsystems/outtake.h"
#include "robot_config.h"
#include "subsystems/intake.h"


OuttakeControl::OuttakeControl()
    : comboMode(false), L1_lastState(false), midScoringMode(false),
      X_lastState(false), unjamStartTime(0), isUnjamming(false) {}

void OuttakeControl::update(IntakeControl &intake) {
  // Handle unjam sequence
  if (isUnjamming) {
    if (pros::millis() - unjamStartTime >= 100) {
      isUnjamming = false;
    } else {
      Intake.move_velocity(600);
      Outtake.move_velocity(-600);
      return;
    }
  }

  // Mid Scoring Toggle (Button X)
  bool X_current = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  if (X_current && !X_lastState) {
    midScoringMode = !midScoringMode;

    if (midScoringMode) {
      comboMode = false;
      MidScoring.set_value(true);
      isUnjamming = true;
      unjamStartTime = pros::millis();
    } else {
      MidScoring.set_value(false);
      isUnjamming = false;
      Intake.move_velocity(0);
      Outtake.move_velocity(0);
      comboMode = false;
      X_lastState = X_current;
      return;
    }
  }
  X_lastState = X_current;

  int velocity = 0;

  if (midScoringMode && !isUnjamming) {
    Intake.move_velocity(-600);
    velocity = -600;
    L1_lastState = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
  } else if (!midScoringMode) {
    bool L1_current = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);

    if (L1_current && !L1_lastState) {
      comboMode = !comboMode;
      if (comboMode) {
        intake.cancelToggles();
      } else {
        Intake.move_velocity(0);
      }
    }

    L1_lastState = L1_current;

    if (comboMode) {
      velocity = -600;
      Intake.move_velocity(600);
    }
  }

  Outtake.move_velocity(velocity);
}

int OuttakeControl::getVelocity() {
  if (midScoringMode)
    return -600;
  if (comboMode)
    return -600;
  return 0;
}

bool OuttakeControl::isMidScoring() { return midScoringMode; }

bool OuttakeControl::isComboMode() { return comboMode; }

void OuttakeControl::cancelCombo() {
  comboMode = false;
  Outtake.move_velocity(0);
}
