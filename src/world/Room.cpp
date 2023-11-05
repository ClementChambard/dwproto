#include "./Room.hpp"
#include "./RoomTransition.hpp"

void Room::testEnv() {
  m_collider.testEnv();
  m_transitions.push_back({this,
                           {-120, -20, 0},
                           {-80, 20, 40},

                           {-100, 0, 0},
                           {100, 0, 0}});
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
}

void Room::fire_event(RoomEvent *ev) {
  for (auto &ro : m_objects)
    ro->on_room_event(ev);
}
