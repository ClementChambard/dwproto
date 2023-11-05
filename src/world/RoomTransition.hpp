#ifndef ROOMTRANSITION_INCLUDED_H
#define ROOMTRANSITION_INCLUDED_H

#include "./Room.hpp"

struct RoomTransition {
  Room *room_to;
  // use an AABB for simplicity
  glm::vec3 coord_low{};
  glm::vec3 coord_high{};

  glm::vec3 reference_pos{};
  glm::vec3 destination{};

  // TODO: transitionKind ?

  void on_tick();
  void on_draw_debug();
};

#endif // !ROOMTRANSITION_INCLUDED_H
