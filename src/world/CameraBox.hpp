#ifndef CAMERABOX_INCLUDED_H
#define CAMERABOX_INCLUDED_H

#include <cstdint>
#include <glm/glm.hpp>

struct CameraBox {
  glm::vec3 coords_low{};
  glm::vec3 coords_high{};

  enum class Dir : uint8_t { X = 0b00, Y = 0b01, Z = 0b10 };
  enum class UseResult : uint8_t {
    NONE = 0,
    USE = 1,
    RECALCULATE = 2,
    USEANDRECALCULATE = 3,
  };

  float yawNeg = 0.0;
  float yawPos = 0.0;
  float angleNeg = 0.0;
  float anglePos = 0.0;
  float distanceNeg = 0.0;
  float distancePos = 0.0;

  struct Flags {
    uint32_t dir : 2;
    uint32_t controlYaw : 1;
    uint32_t controlAngle : 1;
    uint32_t controlDistance : 1;
    uint32_t restrainCamera : 1;
    uint32_t active : 1;
    uint32_t wasActive : 1;
    uint32_t wasRestrained : 1;
    uint32_t usedThisFrame : 1;
    uint32_t _reserved : 23;
  } flags = {
      .dir = (uint8_t)Dir::X,
      .controlYaw = 0,
      .controlAngle = 0,
      .controlDistance = 0,
      .restrainCamera = 0,
      .active = true,
      .wasActive = true,
      .wasRestrained = 0,
      .usedThisFrame = 0,
      ._reserved = 0,
  };

  UseResult shouldBeUsed(glm::vec3 const &playerPos);

  void apply(float *yaw, float *angle, float *distance, glm::vec3 *position);

  void on_draw_debug();
};

#endif // !CAMERABOX_INCLUDED_H
