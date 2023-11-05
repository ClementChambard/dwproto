#include "./RoomTransition.hpp"
#include "../Player.hpp"
#include "./Area.hpp"
#include <NSEngine.h>

bool in(glm::vec3 const &coord_high, glm::vec3 const &coord_low) {
  auto pos = PLAYER_PTR->collider.pos();
  if (pos.x > coord_high.x)
    return false;
  if (pos.y > coord_high.y)
    return false;
  if (pos.z > coord_high.z)
    return false;
  if (pos.x < coord_low.x)
    return false;
  if (pos.y < coord_low.y)
    return false;
  if (pos.z < coord_low.z)
    return false;
  return true;
}

void RoomTransition::on_tick() {
  // check player is in range
  if (in(coord_high, coord_low))
    CURRENT_AREA->trigger_transition(this);
}

void RoomTransition::on_draw_debug() {
  auto x1 = coord_low.x;
  auto y1 = coord_low.y;
  auto z1 = coord_low.z;
  auto x2 = coord_high.x;
  auto y2 = coord_high.y;
  auto z2 = coord_high.z;
  auto col = c_blue;
  if (in(coord_high, coord_low))
    col = c_red;
  NSEngine::draw_quad_color({x1, y1, z1}, {x2, y1, z1}, {x2, y2, z1},
                            {x1, y2, z1}, col, col, col, col, true);
  NSEngine::draw_quad_color({x1, y1, z2}, {x2, y1, z2}, {x2, y2, z2},
                            {x1, y2, z2}, col, col, col, col, true);
  NSEngine::draw_line_color_3d(x1, y1, z1, x1, y1, z2, 1, col, col);
  NSEngine::draw_line_color_3d(x2, y1, z1, x2, y1, z2, 1, col, col);
  NSEngine::draw_line_color_3d(x2, y2, z1, x2, y2, z2, 1, col, col);
  NSEngine::draw_line_color_3d(x1, y2, z1, x1, y2, z2, 1, col, col);
}
