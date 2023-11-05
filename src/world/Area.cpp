#include "./Area.hpp"
#include "../Player.hpp"
#include "./RoomEvent.hpp"

Area *CURRENT_AREA = nullptr;

Area::Area() {
  // do properly
  if (CURRENT_AREA)
    delete CURRENT_AREA;
  CURRENT_AREA = this;
}

void Area::testEnv() {
  m_rooms.push_back(Room{});
  m_rooms.back().testEnv();
  m_current_room = &m_rooms.back();
}

void Area::on_tick() {
  if (m_state == State::PLAYING) {
    if (m_current_room)
      m_current_room->on_tick();
  }

  if (m_state == State::IN_TRANSITION) {
    // at some point, load next room and end state at some other point
    if (m_state_timer == 1) {
      auto evleft = RoomEvent{RoomEventKind::ROOM_LEFT, {}};
      auto eventer = RoomEvent{RoomEventKind::ROOM_LEFT, {}};
      m_current_room->fire_event(&evleft);
      m_current_room = m_active_transition->room_to;
      PLAYER_PTR->collider.inc_pos_no_check(m_active_transition->destination -
                                            m_active_transition->reference_pos);
      m_current_room->fire_event(&eventer);
      m_active_transition = nullptr;
      m_state = State::PLAYING;
    }
    m_state_timer++;
  }
}

void Area::on_draw() {
  if (m_current_room)
    m_current_room->on_draw();
}
