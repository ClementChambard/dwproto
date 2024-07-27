#ifndef EDITORCAMERA_INCLUDED_H
#define EDITORCAMERA_INCLUDED_H

#include "./EditorController.hpp"
#include <cstdint>
#include <glm/glm.hpp>

class EditorCamera : public EditorController {
public:
  glm::vec3 centerPoint{};
  float yaw = 0.f;
  float pitch = 0.f;
  float distance = 100.f;

  EditorCamera();
  ~EditorCamera() override;

  // implementation
  bool wantsControls() override { return m_control != ControlMode::NONE; }
  // void helperImGui() override;
  void onTickGlobal(EditorController *currentController) override;
  void onTickControlled() override;
  // void onDrawGlobal(EditorController *currentController) override;
  // void onDrawControlled() override;

private:
  enum class ControlMode : uint8_t { NONE = 0, ROTATE, PAN, ZOOM };

  ControlMode m_control = ControlMode::NONE;
  glm::vec3 m_look{};

  void recalculate();
};

#endif // !EDITORCAMERA_INCLUDED_H
