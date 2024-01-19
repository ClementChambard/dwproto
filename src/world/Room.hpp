#ifndef ROOM_INCLUDED_H
#define ROOM_INCLUDED_H

#include "./RoomCollider.hpp"
#include "./RoomObject.hpp"
#include "./CameraBox.hpp"
#include <glm/fwd.hpp>
#include <vector>

struct RoomTransition;

class Room {
public:
  RoomCollider const &collider() const { return m_collider; }

  void testEnv();

  void on_tick();
  void on_draw();

  void fire_event(RoomEvent *ev);

  bool cameraBoxes(glm::vec3 const& playerPos, std::vector<CameraBox*>* boxes);

private:
  RoomCollider m_collider;
  std::vector<RoomObject *> m_objects;
  std::vector<RoomTransition> m_transitions;
  std::vector<CameraBox> m_cameraboxes;
};

#endif // !ROOM_INCLUDED_H
