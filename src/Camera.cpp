#include "./Camera.hpp"

#include <NSEngine.h>
#include <glm/ext/matrix_transform.hpp>

#include "./Player.hpp"
#include "world/Area.hpp"
#include "world/CameraBox.hpp"

Camera *Camera::INSTANCE = nullptr;

Camera::Camera() {
  if (INSTANCE)
    delete INSTANCE;
  INSTANCE = this;

  recalculatePosition();
}

Camera::~Camera() { INSTANCE = nullptr; }

#define CAMERA_ANGLE_TRESHOLD 0.03f
#define CAMERA_RELPOS_TRESHOLD 0.1f
#define CAMERA_DISTANCE_TRESHOLD 1.f

#define CAMERA_ANGLE_F 8.f
#define CAMERA_RELPOS_F 8.f
#define CAMERA_DISTANCE_F 8.f

void Camera::on_tick() {
  if (!Player::INSTANCE)
    return;

  // temp
  if (Inputs::Keyboard().Down(NSK_a)) {
    TargetRelpos.y += CAMERA_ANGLE_TRESHOLD;
  }
  if (Inputs::Keyboard().Down(NSK_d)) {
    TargetRelpos.y -= CAMERA_ANGLE_TRESHOLD;
  }
  if (Inputs::Keyboard().Down(NSK_s)) {
    TargetRelpos.x += CAMERA_ANGLE_TRESHOLD;
  }
  if (Inputs::Keyboard().Down(NSK_w)) {
    TargetRelpos.x -= CAMERA_ANGLE_TRESHOLD;
  }
  if (Inputs::Keyboard().Down(NSK_c)) {
    TargetRelpos.z += CAMERA_DISTANCE_TRESHOLD;
  }
  if (Inputs::Keyboard().Down(NSK_v)) {
    TargetRelpos.z -= CAMERA_DISTANCE_TRESHOLD;
  }
  // !temp

  playerPosTarget = Player::INSTANCE->collider.pos();

  std::vector<CameraBox *> boxes;
  bool recalculate = CURRENT_AREA->cameraBoxes(playerPosTarget, &boxes);

  for (auto b : boxes) {
    b->apply(&TargetRelpos.y, &TargetRelpos.x, &TargetRelpos.z,
             &playerPosTarget);
  }

  glm::vec3 relpos = {angleToPlayer, yaw, distanceToPlayer};

  recalculate =
      recalculate || (relpos != TargetRelpos || playerPos != playerPosTarget);

  relpos += (TargetRelpos - relpos) / CAMERA_RELPOS_F;
  if (glm::dot(TargetRelpos - relpos, TargetRelpos - relpos) <
      CAMERA_RELPOS_TRESHOLD)
    relpos = TargetRelpos;

  angleToPlayer = relpos.x;
  yaw = relpos.y;
  distanceToPlayer = relpos.z;

  playerPos += (playerPosTarget - playerPos) / CAMERA_DISTANCE_F;
  if (glm::dot(playerPosTarget - playerPos, playerPosTarget - playerPos) <
      CAMERA_DISTANCE_TRESHOLD * CAMERA_DISTANCE_TRESHOLD)
    playerPos = playerPosTarget;

  if (recalculate) {
    recalculatePosition();
  }
}

void Camera::recalculatePosition() {
  glm::vec3 relativePosition = {
      distanceToPlayer * cos(yaw) * cos(angleToPlayer),
      distanceToPlayer * sin(angleToPlayer),
      distanceToPlayer * sin(yaw) * cos(angleToPlayer)};

  glm::vec3 pos = playerPos + relativePosition;
  NSEngine::activeCamera3D()->setPosition(pos.x, pos.y, pos.z);
  NSEngine::activeCamera3D()->setLook(-relativePosition.x, -relativePosition.y,
                                      -relativePosition.z);
}
