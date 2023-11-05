#ifndef PLAYER_INCLUDED_H
#define PLAYER_INCLUDED_H

#include "./EntityCollider.hpp"

class Player {
public:
  Player();

  void on_tick_debug();
  void on_draw_debug();

  EntityCollider collider;
};

extern Player *PLAYER_PTR;

#endif // !PLAYER_INCLUDED_H
