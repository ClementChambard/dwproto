#ifndef PLAYER_INCLUDED_H
#define PLAYER_INCLUDED_H

#include "./EntityCollider.hpp"

class Player {
public:

  static Player* INSTANCE;

  Player();
  ~Player();

  void on_tick_debug();
  void on_draw_debug();

  EntityCollider collider;
};

#endif // !PLAYER_INCLUDED_H
