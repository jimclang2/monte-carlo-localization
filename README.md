<h1 align="center">Monte Carlo Localization for VEX V5</h1>

<p align="center">
    <a href="https://github.com/uz-g/monte-carlo-localization/pulse"><img src="https://img.shields.io/github/last-commit/uz-g/monte-carlo-localization?style=for-the-badge&logo=github&color=7dc4e4&logoColor=D9E0EE&labelColor=302D41"></a>
    <a href="https://github.com/uz-g/monte-carlo-localization/stargazers"><img src="https://img.shields.io/github/stars/uz-g/monte-carlo-localization?style=for-the-badge&logo=apachespark&color=eed49f&logoColor=D9E0EE&labelColor=302D41"></a>
</p>

This project implements an advanced motion control system for the VEX V5 platform, with a core focus on **Monte Carlo Localization (MCL)**, updated for the **VEX Push Back** competition season. It utilizes PROS and LemLib.

> **Note:** This codebase was originally built for High Stakes and has been cleaned up as a template for Push Back. Hardware ports, PID values, and autonomous routines are **placeholders** that must be configured for your new robot.

## 🚀 Core Feature: Monte Carlo Localization

At the heart of this system is a full-featured Monte Carlo Localization (MCL) engine, implemented in [`src/monte.cpp`](src/monte.cpp). MCL enables the robot to:

- Precisely estimate its global position and orientation on the field, even with noisy or imperfect sensor data
- Fuse data from IMU, tracking wheels, and multiple distance sensors for maximum reliability
- Continuously correct for odometry drift, wheel slip, and field inconsistencies
- Power advanced autonomous routines and complex path planning

## 🧠 MCL Update Cycle

1. **Motion Update (Prediction):** Predicts the robot's new pose based on odometry movement
2. **Measurement Update (Correction):** Adjusts particle weights using distance sensor measurements
3. **Resampling:** Resamples the particle set to focus on the most likely poses
4. **Pose Estimation:** Computes the estimated position with exponential smoothing

### Push Back Considerations

Push Back Goals are physical structures on the field that **will obstruct distance sensors**. The MCL sensor model (`predictSensorReading`) currently only accounts for field perimeter walls. You should:

- Use the sensor enable/disable flags (`useNorthSensor`, etc.) to turn off sensors aimed at Goals
- Consider adding Goal bounding boxes to the sensor model for more accurate predictions
- Filter out unexpectedly short readings that are likely hitting Goal structures

## ⚙️ Hardware Configuration

All hardware is defined in [`src/globals.cpp`](src/globals.cpp). **All ports and values are placeholders — update them for your robot.**

- **Drivetrain:** 3 motors per side (configured for blue cartridges)
- **Sensors:** IMU, horizontal tracking wheel, 4 distance sensors
- **Pneumatics:** 1 ADI pneumatic
- **Subsystem motors:** TBD — define your Push Back mechanisms

## 🕹️ Driver Control

Tank drive is configured. Mechanism controls are stubbed out in [`src/main.cpp`](src/main.cpp).

**Push Back timing:**
- Autonomous Period: 15 seconds
- Driver Controlled Period: 1:45 (105 seconds)
- Endgame (Park Zone protection): last 20 seconds

## 🤖 Autonomous Modes

Stub routines are in [`src/auto.cpp`](src/auto.cpp):

- **redNeg** / **redPos** — Red alliance routines
- **blueNeg** / **bluePos** — Blue alliance routines
- **skills** — Skills challenge ([`src/skills.cpp`](src/skills.cpp))

## 📁 Key Files

| File | Purpose |
|---|---|
| `src/main.cpp` | Init, driver control, GUI |
| `src/auto.cpp` | Match autonomous stubs |
| `src/skills.cpp` | Skills autonomous stub |
| `src/monte.cpp` | **MCL engine** (preserved from High Stakes) |
| `src/globals.cpp` | Hardware definitions (all ports are placeholders) |
| `include/globals.h` | Hardware declarations |
| `include/robot/monte.hpp` | MCL API header |

## 📚 Libraries

- [PROS 4.1.1](https://pros.cs.purdue.edu/v5/pros-4/) — C/C++ SDK for VEX V5
- [LemLib 0.5.5](https://lemlib.readthedocs.io/) — Drivetrain control and odometry
- [LVGL 8.3.8](https://docs.lvgl.io/master/) — Brain screen graphics
- [Robodash 2.3.0](https://github.com/unwieldycat/robodash) — Autonomous selector GUI

## 🏗️ Building

```bash
pros m
```

## 🔌 Flashing to V5 Brain

```bash
pros u
```

## 📝 License

This project is currently unlicensed.
