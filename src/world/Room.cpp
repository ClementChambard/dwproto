#include "./Room.hpp"
#include "./RoomTransition.hpp"
#include "CameraBox.hpp"

void Room::testEnv() {
  m_collider.testEnv();
  m_transitions.push_back({this,
                           {-120, -20, 0},
                           {-80, 20, 40},

                           {-100, 0, 0},
                           {100, 0, 0}});

  m_cameraboxes.push_back({
      .coords_low = {-40, 0, 80},
      .coords_high = {40, 200, 160},
      .yawNeg = 0.f,
      .yawPos = 1.52f,
      .angleNeg = 1.4f,
      .anglePos = 0.8f,
      .distanceNeg = 200.f,
      .distancePos = 100.f,
      .flags = {.dir = (uint8_t)CameraBox::Dir::Z,
                .controlYaw = true,
                .controlAngle = true,
                .controlDistance = true,
                .restrainCamera = false,
                .active = true,
                .wasActive = true,
                .wasRestrained = false,
                .usedThisFrame = false,
                ._reserved = 0},
  });

  m_cameraboxes.push_back({
      .coords_low = {-50, 0, -50},
      .coords_high = {50, 100, 50},
      .flags = {.dir = (uint8_t)CameraBox::Dir::Z,
                .controlYaw = false,
                .controlAngle = false,
                .controlDistance = false,
                .restrainCamera = true,
                .active = true,
                .wasActive = true,
                .wasRestrained = false,
                .usedThisFrame = false,
                ._reserved = 0},
  });
}

void Room::on_tick() {
  for (auto ro : m_objects)
    ro->on_tick();
  for (auto &rt : m_transitions)
    rt.on_tick();
}

void Room::on_draw() {
  for (auto ro : m_objects)
    ro->on_draw();
  // if debug draw collider
  m_collider.debug_draw();
  for (auto &rt : m_transitions)
    rt.on_draw_debug();

  for (auto &cb : m_cameraboxes)
    cb.on_draw_debug();
}

void Room::fire_event(RoomEvent *ev) {
  for (auto &ro : m_objects)
    ro->on_room_event(ev);
}

bool Room::cameraBoxes(glm::vec3 const &playerPos,
                       std::vector<CameraBox *> *boxes) {
  if (!boxes)
    return false;

  bool r = false;
  for (auto &b : m_cameraboxes) {
    auto result = b.shouldBeUsed(playerPos);
    if (result == CameraBox::UseResult::USE) {
      boxes->push_back(&b);
    } else if (result == CameraBox::UseResult::RECALCULATE) {
      r = true;
    } else if (result == CameraBox::UseResult::USEANDRECALCULATE) {
      r = true;
      boxes->push_back(&b);
    }
  }

  return r;
}
