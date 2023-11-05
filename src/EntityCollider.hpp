#ifndef ENTITYCOLLIDER_INCLUDED_H
#define ENTITYCOLLIDER_INCLUDED_H

#include "world/RoomCollider.hpp"
#include <glm/glm.hpp>

class EntityCollider {
public:
  EntityCollider() { f_on_ground = 0; }

  void resolve(RoomCollider const &rc);

  glm::vec3 pos() const { return m_pos; }
  void inc_pos(glm::vec3 const &inc) { m_pos += inc; }
  void inc_pos_no_check(glm::vec3 const &inc) {
    m_pos += inc;
    m_prev_pos = m_pos;
  }
  void set_pos(glm::vec3 const &pos) { m_pos = pos; }
  bool on_ground() const { return f_on_ground; }

private:
  glm::vec3 m_pos{};
  glm::vec3 m_prev_pos{};
  int m_plat_id_p = -1;

  // flags
  int32_t f_on_ground : 1;
  int32_t f_unused : 31;
};

#endif // !ENTITYCOLLIDER_INCLUDED_H
