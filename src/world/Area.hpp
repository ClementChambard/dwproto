#ifndef AREA_INCLUDED_H
#define AREA_INCLUDED_H

#include "../EntityCollider.hpp"
#include "./Room.hpp"
#include "./RoomTransition.hpp"
#include <vector>

class Area {

public:
  Area();
  void testEnv();

  void on_tick();
  void on_draw();

  void resolveCollisions(EntityCollider &collider) const {
    collider.resolve(m_current_room->collider());
  }

  void trigger_transition(RoomTransition *rt) {
    m_active_transition = rt;
    m_state = State::IN_TRANSITION;
    m_state_timer = 0;
  }

private:
  enum class State {
    PLAYING,
    IN_TRANSITION,
  } m_state = State::PLAYING;
  uint32_t m_state_timer = 0;

  std::vector<Room> m_rooms{};
  Room *m_current_room = nullptr;
  RoomTransition *m_active_transition = nullptr;
  // anm loaded here
};

extern Area *CURRENT_AREA;

#endif // !AREA_INCLUDED_H
