#ifndef ROOMCOLLIDER_INCLUDED_H
#define ROOMCOLLIDER_INCLUDED_H

#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class RoomCollider {
public:
  RoomCollider() = default;
  void load(uint8_t *data, size_t data_len);

  // debug only
  void testEnv();
  // debug only
  void debug_draw() const;

  std::vector<size_t> get_intersection_planes(float x, float z) const;

  void wallcheck(float &x, float y, float &z, float xp, float zp) const;

  struct Wall {
    // The points should be set in "clockwise" order in order for the normal
    // vector to be calculated properly
    // maybe add "normal_vector" field ?
    glm::vec2 point_xz_1{};
    glm::vec2 point_xz_2{};
    float elevation_low = 0.f;
    float elevation_high = 0.f;
  };
  enum class PlaneSlopeType {
    HORIZONTAL,
    X_VARIES,
    Z_VARIES,
  };
  struct Plane {
    // a plane is axis aligned. coord_low has the coordinate with lower
    // component value and coord_high has the higher component value
    glm::vec2 coord_low{};
    glm::vec2 coord_high{};
    float elevation_at_low_coord = 0.f;
    float elevation_at_high_coord = 0.f;
    PlaneSlopeType slope_type = PlaneSlopeType::HORIZONTAL;

    bool is_on(float x, float z) const;

    float elevation(float x, float z) const;
    bool should_go_to(Plane const &p2, glm::vec2 prev, glm::vec2 now) const;
  };

  Wall const &wall(size_t i) const { return m_walls[i]; }
  Plane const &plane(size_t i) const { return m_planes[i]; }

private:
  std::vector<Wall> m_walls{};
  std::vector<Plane> m_planes{};
};

#endif // !ROOMCOLLIDER_INCLUDED_H
