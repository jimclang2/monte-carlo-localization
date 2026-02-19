#include "curves.h"
#include <algorithm>

// ============================================================
// Joystick Curve Implementations
// ============================================================
// All curves map input (-127..127) → output (-127..127).
// The sign is always preserved so negative stick = negative output.

int applyCurve(int input, CurveType curve, double param) {
  // Clamp input to valid joystick range
  input = std::clamp(input, -127, 127);

  // Normalize to -1.0 .. 1.0
  double x = input / 127.0;
  double sign = (x < 0) ? -1.0 : 1.0;
  double ax = std::abs(x); // work with positive magnitude
  double result = 0.0;

  switch (curve) {

  case CurveType::LINEAR:
    result = ax;
    break;

  case CurveType::SQUARED:
    result = ax * ax;
    break;

  case CurveType::CUBED:
    result = ax * ax * ax;
    break;

  case CurveType::EXPONENTIAL: {
    double k = (param > 0.01) ? param : 1.5;
    result = (std::exp(k * ax) - 1.0) / (std::exp(k) - 1.0);
    break;
  }

  case CurveType::S_CURVE: {
    double k = 3.0;
    double raw = std::tanh(k * (ax - 0.5));
    double lo = std::tanh(k * (0.0 - 0.5));
    double hi = std::tanh(k * (1.0 - 0.5));
    result = (raw - lo) / (hi - lo);
    break;
  }

  case CurveType::PIECEWISE: {
    double bp = (param > 0.01) ? param : 0.3;
    double low_out = 0.15;
    if (ax <= bp) {
      result = (low_out / bp) * ax;
    } else {
      result = low_out + ((1.0 - low_out) / (1.0 - bp)) * (ax - bp);
    }
    break;
  }
  }

  int output = static_cast<int>(sign * result * 127.0);
  return std::clamp(output, -127, 127);
}

std::string getCurveName(CurveType curve) {
  switch (curve) {
  case CurveType::LINEAR:
    return "Linear";
  case CurveType::SQUARED:
    return "Squared";
  case CurveType::CUBED:
    return "Cubed";
  case CurveType::EXPONENTIAL:
    return "Exponential";
  case CurveType::S_CURVE:
    return "S-Curve";
  case CurveType::PIECEWISE:
    return "Piecewise";
  default:
    return "Unknown";
  }
}

CurveType nextCurve(CurveType current) {
  int next = (static_cast<int>(current) + 1) % 6;
  return static_cast<CurveType>(next);
}
