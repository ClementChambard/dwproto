#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>

class Camera {
public:
  Camera();
  ~Camera();

  static Camera *INSTANCE;

  void on_tick();
  // void on_draw();

  glm::vec3 playerPos{};
  glm::vec3 playerPosTarget{};

  float angleToPlayer = 1.4f;
  float yaw = 0.f;
  float distanceToPlayer = 200.f;
  glm::vec3 TargetRelpos = {1.4f, 0.f, 200.f};

private:
  void recalculatePosition();
};

#endif // !CAMERA_INCLUDED_H
