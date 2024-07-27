#include "./CameraBox.hpp"

#include <NSEngine.h>
#include <glm/common.hpp>
#include <iostream>

CameraBox::UseResult CameraBox::shouldBeUsed(glm::vec3 const &playerPos) {
  if (flags.wasRestrained) {
    flags.usedThisFrame = flags.active;
    if (flags.active) {
      return UseResult::USE;
    } else {
      flags.wasRestrained = false;
      return UseResult::RECALCULATE;
    }
  }

  if (!flags.active) {
    flags.usedThisFrame = false;
    return UseResult::NONE;
  }

  if (playerPos.x >= coords_low.x && playerPos.y >= coords_low.y &&
      playerPos.z >= coords_low.z && playerPos.x <= coords_high.x &&
      playerPos.y <= coords_high.y && playerPos.z <= coords_high.z) {
    flags.usedThisFrame = true;
    if (flags.active != flags.wasActive) {
      flags.wasActive = flags.active;
      return UseResult::USEANDRECALCULATE;
    }
    return UseResult::USE;
  }

  if (flags.usedThisFrame) {
    flags.usedThisFrame = false;
    if (flags.active != flags.wasActive) {
      flags.wasActive = flags.active;
      return UseResult::USEANDRECALCULATE;
    }
    return UseResult::USE;
  }

  flags.usedThisFrame = false;
  return UseResult::NONE;
}

void CameraBox::apply(float *yaw, float *angle, float *distance,
                      glm::vec3 *position) {
  if (flags.restrainCamera) {
    flags.wasRestrained = true;
    position->x = glm::clamp(position->x, coords_low.x, coords_high.x);
    position->y = glm::clamp(position->y, coords_low.y, coords_high.y);
    position->z = glm::clamp(position->z, coords_low.z, coords_high.z);
  }

  float ratio = 0.f;

  if ((Dir)flags.dir == Dir::X && coords_high.x != coords_low.x) {
    ratio = (position->x - coords_low.x) / (coords_high.x - coords_low.x);
  }
  if ((Dir)flags.dir == Dir::Y && coords_high.y != coords_low.y) {
    ratio = (position->y - coords_low.y) / (coords_high.y - coords_low.y);
  }
  if ((Dir)flags.dir == Dir::Z && coords_high.z != coords_low.z) {
    ratio = (position->z - coords_low.z) / (coords_high.z - coords_low.z);
  }
  if (ratio < 0.f)
    ratio = 0.f;
  if (ratio > 1.f)
    ratio = 1.f;

  // TODO(ClementChambard): multiple interpolation methods
  if (flags.controlYaw)
    *yaw = yawNeg + ratio * (yawPos - yawNeg);
  if (flags.controlDistance)
    *distance = distanceNeg + ratio * (distancePos - distanceNeg);
  if (flags.controlAngle)
    *angle = angleNeg + ratio * (anglePos - angleNeg);

  yaw = 0;
  angle = 0;
  distance = 0;
}

void CameraBox::on_draw_debug() {
  // test
  if (Inputs::Keyboard().Pressed(NSK_b)) {
    flags.active = !flags.active;
  }

  // auto x1 = coords_low.x;
  // auto y1 = coords_low.y;
  // auto z1 = coords_low.z;
  // auto x2 = coords_high.x;
  // auto y2 = coords_high.y;
  // auto z2 = coords_high.z;
  // auto col = c_blue;
  // if (flags.usedThisFrame)
  //   col = c_red;
  // NSEngine::draw_quad_color({x1, y1, z1}, {x2, y1, z1}, {x2, y2, z1},
  //                           {x1, y2, z1}, col, col, col, col, true);
  // NSEngine::draw_quad_color({x1, y1, z2}, {x2, y1, z2}, {x2, y2, z2},
  //                           {x1, y2, z2}, col, col, col, col, true);
  // NSEngine::draw_line_color_3d(x1, y1, z1, x1, y1, z2, 1, col, col);
  // NSEngine::draw_line_color_3d(x2, y1, z1, x2, y1, z2, 1, col, col);
  // NSEngine::draw_line_color_3d(x2, y2, z1, x2, y2, z2, 1, col, col);
  // NSEngine::draw_line_color_3d(x1, y2, z1, x1, y2, z2, 1, col, col);
}
