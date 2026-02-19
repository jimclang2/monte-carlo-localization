# Setup TODO — Monte Carlo Localization

## ✅ Done (code is already merged)

- [x] Main-Drive code ported (subsystems, curves, autons, driver control)
- [x] MCL engine included (`monte.cpp` + `monte.hpp`)
- [x] Distance sensor declarations added to `robot_config`
- [x] `stopMCL()` hooked into `opcontrol()`
- [x] `startMCL()` / `stopMCL()` ready in `autonomous.cpp` (commented out)

---

## 🔨 Step 1: Build & Test (no hardware changes needed)

- [ ] Open project in VS Code with PROS extension
- [ ] Hit **Build** — fix any compile errors
- [ ] Flash to brain, test driver control works exactly like before
- [ ] Test autons work exactly like before
- [ ] **Nothing should change yet** — MCL is off until you uncomment it

---

## 🔧 Step 2: Mount Distance Sensors

- [ ] Get 4x VEX V5 Distance Sensors
- [ ] Mount them on the robot pointing **outward at field walls**:
  - North (front), South (back), East (right), West (left)
  - Doesn't need to be perfect — just roughly in those directions
- [ ] Wire them to the brain on any available smart ports
- [ ] **Measure sensor offsets** (distance from each sensor to the robot's tracking center, in inches)

---

## 🔌 Step 3: Update Ports in Code

Open `src/robot_config.cpp` and update **lines 85-88**:

```cpp
// CHANGE THESE to your actual ports:
pros::Distance dNorth(1);  // ← your north sensor port
pros::Distance dSouth(2);  // ← your south sensor port
pros::Distance dEast(3);   // ← your east sensor port
pros::Distance dWest(4);   // ← your west sensor port
```

Then open `src/monte.cpp` and update the **sensor offsets** (search for `SENSOR_X_OFFSET` and `SENSOR_Y_OFFSET`) to match your measured values.

---

## 🚀 Step 4: Enable MCL in Autonomous

Open `src/autonomous.cpp` and uncomment the MCL lines in `skills_auton()`:

```cpp
void skills_auton() {
    startMCL(chassis);  // ← uncomment this

    // ... your auton moves ...

    stopMCL();          // ← uncomment this
}
```

---

## 🎯 Step 5: Handle Goal Obstructions

Goals on the field will block distance sensors. Toggle sensors off when near Goals:

```cpp
// Example: robot is near west Goal, west sensor would hit it
useWestSensor = false;

chassis.moveToPoint(-32.5, 5, 1550);  // move past the Goal

// Past the Goal now, west sensor sees wall again
useWestSensor = true;
```

**Available flags** (in `monte.cpp`, all default to `false`):
- `useNorthSensor`
- `useSouthSensor`
- `useEastSensor`
- `useWestSensor`

**Rule of thumb:** if in doubt, leave the sensor OFF. A disabled sensor doesn't hurt. A sensor reading a Goal when MCL expects a wall *actively hurts*.

---

## 🧪 Step 6: Test & Tune

- [ ] Run skills auton with MCL enabled
- [ ] Watch the brain screen — MCL displays particle spread and estimated pose
- [ ] Compare final position accuracy with MCL on vs off
- [ ] If MCL makes things worse, check:
  - Are sensor offsets measured correctly?
  - Are sensors pointing at walls or at Goals?
  - Are the sensor toggle flags set correctly?

---

## 📁 File Reference

| File | What's in it |
|---|---|
| `src/robot_config.cpp` | **Sensor ports** — update lines 85-88 |
| `src/autonomous.cpp` | **MCL start/stop** — uncomment when ready |
| `src/monte.cpp` | **MCL engine** — sensor offsets, toggle flags, tuning constants |
| `include/robot/monte.hpp` | MCL function declarations |

---

## ⚡ Quick Start (if you just want to test MCL fast)

1. Mount **even just 1 sensor** (e.g. west-facing)
2. Update its port in `robot_config.cpp`
3. In `autonomous.cpp`, add:
   ```cpp
   useWestSensor = true;
   startMCL(chassis);
   ```
4. Run an auton and see if endpoint accuracy improves

You don't need all 4 sensors to start. One reliable wall-facing sensor is enough to see MCL working.
