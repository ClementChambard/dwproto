#include "./EditorCamera.hpp"

#include <NSEngine.h>

#include <glm/ext/quaternion_geometric.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>

EditorCamera::EditorCamera() {}

EditorCamera::~EditorCamera() {}

void EditorCamera::onTickGlobal(EditorController *currentController) {
  if (currentController) {
    recalculate();
    return;
  }

  // mouse should be in display window

  if (Inputs::Mouse().Pressed(NSM_middleclick)) {
    if (Inputs::Keyboard().Down(NSK_lshift) ||
        Inputs::Keyboard().Down(NSK_rshift)) {
      m_control = ControlMode::PAN;
    } else if (Inputs::Keyboard().Down(NSK_lctrl) ||
               Inputs::Keyboard().Down(NSK_rctrl)) {
      m_control = ControlMode::ZOOM;
    } else {
      m_control = ControlMode::ROTATE;
    }
  } else {
    m_control = ControlMode::NONE;
  }

  if (Inputs::Mouse().scrollUp) {
    distance -= 20.f;
    recalculate();
  }

  if (Inputs::Mouse().scrollDown) {
    distance += 20.f;
    recalculate();
  }
}

#define ZOOM_PIXEL_FACTOR -5.f
#define YAW_PIXEL_FACTOR 0.01f
#define PITCH_PIXEL_FACTOR 0.01f
#define MOVE_PIXEL_FACTOR -0.001f

void EditorCamera::onTickControlled() {
  if (Inputs::Mouse().Released(NSM_middleclick)) {
    m_control = ControlMode::NONE;
    return;
  }

  auto move = Inputs::Mouse().posDiff;

  if (move.y == 0.0 && move.x == 0.0)
    return;

  if (m_control == ControlMode::ZOOM) {
    float z = move.y * ZOOM_PIXEL_FACTOR;
    distance += z;
  }

  if (m_control == ControlMode::PAN) {
    glm::vec3 right =
        glm::normalize(glm::cross(m_look, glm::vec3(0.f, 1.f, 0.f)));
    glm::vec3 up = glm::normalize(glm::cross(right, m_look));

    centerPoint += right * MOVE_PIXEL_FACTOR * move.x * distance;
    centerPoint += up * MOVE_PIXEL_FACTOR * move.y * distance;
  }

  if (m_control == ControlMode::ROTATE) {
    yaw += move.x * YAW_PIXEL_FACTOR;
    if (yaw >= glm::two_pi<float>())
      yaw -= glm::two_pi<float>();
    if (yaw < 0)
      yaw += glm::two_pi<float>();
    pitch += move.y * PITCH_PIXEL_FACTOR;
    if (pitch >= glm::half_pi<float>() - 0.01f)
      pitch = glm::half_pi<float>() - 0.01f;
    if (pitch <= -glm::half_pi<float>() + 0.01f)
      pitch = -glm::half_pi<float>() + 0.01f;
  }

  recalculate();
}

void EditorCamera::recalculate() {
  m_look = glm::vec3(distance * cos(yaw) * cos(pitch), distance * sin(pitch),
                     distance * sin(yaw) * cos(pitch));

  glm::vec3 pos = centerPoint - m_look;

  NSEngine::activeCamera3D()->setPosition(pos.x, pos.y, pos.z);
  NSEngine::activeCamera3D()->setLook(m_look.x, m_look.y, m_look.z);
}
