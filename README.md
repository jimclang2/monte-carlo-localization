<h1 align="center">Monte Carlo Localization for VEX V5</h1>

<p align="center">
    <a href="https://github.com/uz-g/monte-carlo-localization/pulse"><img src="https://img.shields.io/github/last-commit/uz-g/monte-carlo-localization?style=for-the-badge&logo=github&color=7dc4e4&logoColor=D9E0EE&labelColor=302D41"></a>
    <a href="https://github.com/uz-g/monte-carlo-localization/stargazers"><img src="https://img.shields.io/github/stars/uz-g/monte-carlo-localization?style=for-the-badge&logo=apachespark&color=eed49f&logoColor=D9E0EE&labelColor=302D41"></a>
</p>

This project implements an advanced motion control system for the VEX V5 platform, with a core focus on **Monte Carlo Localization (MCL)**, designed for the VEX High Stakes competition season. It utilizes PROS and LemLib.

## 🚀 Core Feature: Monte Carlo Localization

At the heart of this system is a full-featured Monte Carlo Localization (MCL) engine, implemented in [`src/monte.cpp`](src/monte.cpp). MCL enables the robot to:

- Precisely estimate its global position and orientation on the field, even with noisy or imperfect sensor data
- Fuse data from IMU, tracking wheels, and multiple distance sensors for maximum reliability
- Continuously correct for odometry drift, wheel slip, and field inconsistencies
- Power advanced autonomous routines and complex path planning

## Why Monte Carlo Localization?

Traditional VEX V5 robots rely on odometry and IMU sensors for local movement tracking. However, these methods are prone to accumulating errors and can be disrupted by real-world factors like wheel slip or field imperfections, leading to unreliable autonomous performance.

**Monte Carlo Localization (MCL)** solves these problems by maintaining a probabilistic estimate of the robot's global position. By fusing multiple sensor inputs and using a particle filter, MCL delivers:

- Robust, accurate global position tracking
- Resilience to sensor noise and field inconsistencies
- Consistent, repeatable autonomous routines

This approach directly addresses the root causes of autonomous failures and elevates the reliability of VEX V5 robots in competition.

## 🛠️ General Features

- Dual joystick tank drive with an exponential drive curve
- Autonomous mode selection via LVGL GUI
- Intake control system
- Pneumatic systems for mobile goal clamp
- Temperature monitoring for drivetrain and intake motors
- Reverse drive functionality
- Match timer with controller rumble alert
- Numerous driver convenience features

## ⚙️ Hardware Configuration

- **Drivetrain:** 3 motors per side (66W)
- **Intake:** 1.5 motors (16.5W)
- **Lady Brown:** 0.5 motors (5.5W)
- **Sensors:**
    - IMU
    - Horizontal tracking wheel
    - 4 Distance sensors
- **Pneumatics:**
    - Mobile goal clamp (large)

## 🕹️ Usage

1. Flash the program to your VEX V5 brain.
2. Run the program.
3. Use the LVGL GUI on the brain screen to select an autonomous mode.
4. In driver control:
    - Left/Right Joysticks: Control drivetrain
    - R1/R2 Buttons: Control intake
    - L1 Button: Toggle mobile goal clamp
    - L2 Button: Toggle intake position
    - B Button: Toggle reverse drive

## 🤖 Autonomous Modes

- **Close Side (Default)**
- **Far Side**
- **Skills**
- **Off**

Autonomous routines are implemented in [`src/auto.cpp`](src/auto.cpp) and [`src/skills.cpp`](src/skills.cpp).

## 🧠 Monte Carlo Localization Update Cycle

The following diagram illustrates the core Monte Carlo Localization (MCL) update cycle implemented in this project:

<p align="center">
  <img src="include/mcl.png" alt="Monte Carlo Localization Update Cycle" width="900"/>
</p>

This function demonstrates the essential steps of MCL:

1. **Motion Update (Prediction):** Predicts the robot's new pose based on odometry (robot movement).
2. **Measurement Update (Correction):** Adjusts the particle weights using distance sensor measurements.
3. **Resampling:** Resamples the particle set based on their weights to focus on the most likely poses.
4. **Pose Estimation:** Computes the robot's estimated position and updates the chassis accordingly.

This cycle enables robust and accurate localization on the VEX V5 platform, even in the presence of sensor noise and uncertainty.

## 📁 Key Files and Directories

- [`src/main.cpp`](src/main.cpp): Main entry point, driver control logic, and GUI interaction
- [`src/auto.cpp`](src/auto.cpp): Autonomous routines for matches
- [`src/skills.cpp`](src/skills.cpp): Autonomous routines for skills challenges
- [`src/monte.cpp`](src/monte.cpp): Monte Carlo Localization implementation
- [`src/globals.cpp`](src/globals.cpp): Global variables
- [`include/main.h`](include/main.h): Header for main logic
- [`include/globals.h`](include/globals.h): Header for globals
- [`include/robot/`](include/robot/): Robot-specific configurations and classes
- [`liblvgl/`](liblvgl/): LVGL graphics library
- [`lemlib/`](lemlib/): LemLib drivetrain and odometry library
- [`project.pros`](project.pros): PROS project configuration
- [`Makefile`](Makefile): Build instructions

## 📚 Libraries Used

- [PROS](https://pros.cs.purdue.edu/v5/pros-4/): C/C++ SDK for VEX V5
- [LemLib](https://lemlib.readthedocs.io/): Advanced drivetrain control and odometry
- [LVGL](https://docs.lvgl.io/master/): Lightweight graphics library for embedded systems

## 🏗️ Building the Project

1. Ensure you have the PROS CLI installed.
2. Navigate to the project root in your terminal.
3. Run:
   ```sh
   pros m
   ```

## 🔌 Flashing to V5 Brain

1. Connect your VEX V5 Brain to your computer.
2. Run:
   ```sh
   pros u
   ```

## 📝 License

This project is currently unlicensed.
