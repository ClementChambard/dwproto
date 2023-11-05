#include "./EntityCollider.hpp"

void EntityCollider::resolve(RoomCollider const &rc) {
  // if on_ground, position should only have changed x/z
  if (f_on_ground) {
    // if still on same platform:
    if (m_plat_id_p >= 0 && rc.plane(m_plat_id_p).is_on(m_pos.x, m_pos.z)) {
      // snap to it if y is eq or below
      float yplat = rc.plane(m_plat_id_p).elevation(m_pos.x, m_pos.z);
      if (m_pos.y <= yplat || m_pos.y <= m_prev_pos.y)
        m_pos.y = yplat;
      else
        f_on_ground = false;
    } else if (m_plat_id_p >= 0) {
      // find new platform:
      std::vector<size_t> platforms_to_check =
          rc.get_intersection_planes(m_pos.x, m_pos.z);
      RoomCollider::Plane const &old_p = rc.plane(m_plat_id_p);
      int new_plat = -1;
      int highest_plat_below = -1;
      float highest_below = -1000000.f;
      for (auto p : platforms_to_check) {
        float ph = rc.plane(p).elevation(m_pos.x, m_pos.z);
        if (ph > highest_below && ph <= m_pos.y) {
          highest_plat_below = p;
          highest_below = ph;
        }
        if (old_p.should_go_to(rc.plane(p), {m_prev_pos.x, m_prev_pos.z},
                               {m_pos.x, m_pos.z})) {
          new_plat = p;
          // should only match one
          break;
        }
      }
      if (new_plat >= 0) {
        // snap to it
        m_plat_id_p = new_plat;
        float yplat = rc.plane(m_plat_id_p).elevation(m_pos.x, m_pos.z);
        if (m_pos.y <= yplat || m_pos.y <= m_prev_pos.y)
          m_pos.y = yplat;
        else
          f_on_ground = false;
      } else {
        m_plat_id_p = highest_plat_below;
        f_on_ground = false;
      }
    } else {
      // should not happen
    }
  } else {
    // if a platform was below before and is now above, snap to it and set
    // on_ground check only plat_id_p and results of get_intersection_plat.
    std::vector<size_t> platforms_to_check =
        rc.get_intersection_planes(m_pos.x, m_pos.z);
    // if (plat_id_p >= 0)
    //   platforms_to_check.push_back(plat_id_p);

    m_plat_id_p = -1;
    float highest_below = -1000000.f;
    for (auto p : platforms_to_check) {
      float ph = rc.plane(p).elevation(m_pos.x, m_pos.z);
      if (ph > highest_below && ph <= m_pos.y) {
        m_plat_id_p = p;
        highest_below = ph;
      }

      RoomCollider::Plane const &pl = rc.plane(p);
      float yplat_p = pl.elevation(m_prev_pos.x, m_prev_pos.z);
      float yplat = pl.elevation(m_pos.x, m_pos.z);
      if ((yplat - m_pos.y) * (yplat_p - m_prev_pos.y) <= 0) {
        // snap
        m_pos.y = yplat;
        f_on_ground = true;
        m_plat_id_p = p;
        // there should be only one platform crossing the path at a time
        break;
      }
    }
  }

  rc.wallcheck(m_pos.x, m_pos.y, m_pos.z, m_prev_pos.x, m_prev_pos.z);

  m_prev_pos = m_pos;
}
