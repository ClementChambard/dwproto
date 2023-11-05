#include "./RoomCollider.hpp"
#include "../util/DataReader.hpp"
#include <NSEngine.h>

void RoomCollider::load(uint8_t *data, size_t data_len) {
  DataReader dr(data, data_len);
  // first 2 words: wall_count, plane_count
  uint32_t wall_count = dr.u32();
  uint32_t plane_count = dr.u32();
  for (size_t i = 0; i < wall_count; i++) {
    Wall w;
    w.point_xz_1 = dr.v2();
    w.point_xz_2 = dr.v2();
    w.elevation_low = dr.f32();
    w.elevation_high = dr.f32();
    m_walls.push_back(w);
  }
  for (size_t i = 0; i < plane_count; i++) {
    Plane p;
    p.coord_low = dr.v2();
    p.coord_high = dr.v2();
    p.elevation_at_low_coord = dr.f32();
    p.elevation_at_high_coord = dr.f32();
    int32_t elevation_type = dr.i32();
    if (elevation_type == 0) {
      p.slope_type = PlaneSlopeType::HORIZONTAL;
    } else if (elevation_type == 1) {
      p.slope_type = PlaneSlopeType::X_VARIES;
    } else {
      p.slope_type = PlaneSlopeType::Z_VARIES;
    }
    m_planes.push_back(p);
  }
}

void RoomCollider::testEnv() {
  m_planes.push_back(
      {{-100, -100}, {100, 100}, 0, 0, PlaneSlopeType::HORIZONTAL});
  m_planes.push_back({{-50, 100}, {50, 200}, 0, 50, PlaneSlopeType::Z_VARIES});
  m_planes.push_back(
      {{-40, -100}, {40, 250}, -100, -100, PlaneSlopeType::HORIZONTAL});
  m_walls.push_back({{-100, -90}, {100, -90}, 0, 50});
  m_walls.push_back({{45, 100}, {45, 200}, 0, 60});
}

void RoomCollider::debug_draw() const {
  for (auto const &wall : m_walls) {
    float x1 = wall.point_xz_1.x;
    float z1 = wall.point_xz_1.y;
    float x2 = wall.point_xz_2.x;
    float z2 = wall.point_xz_2.y;
    NSEngine::draw_quad_color(
        {x1, wall.elevation_high, z1}, {x2, wall.elevation_high, z2},
        {x2, wall.elevation_low, z2}, {x1, wall.elevation_low, z1}, c_green,
        c_green, c_green, c_green);
  }

  float lowest = 10000000.f;
  float highest = -10000000.f;
  for (auto const &plane : m_planes) {
    if (lowest > plane.elevation_at_high_coord)
      lowest = plane.elevation_at_high_coord;
    if (lowest > plane.elevation_at_low_coord)
      lowest = plane.elevation_at_low_coord;
    if (highest < plane.elevation_at_high_coord)
      highest = plane.elevation_at_high_coord;
    if (highest < plane.elevation_at_low_coord)
      highest = plane.elevation_at_low_coord;
  }
  float gradient_start = lowest - (highest - lowest) / 2;
  float gradient_factor = 2 * (highest - lowest);
  // function: (elevation - gradient_start) / gradient_factor

  for (auto const &plane : m_planes) {
    float etl, etr, ebr, ebl;
    NSEngine::Color ctl, ctr, cbr, cbl;
    if (plane.slope_type == PlaneSlopeType::X_VARIES) {
      etl = ebl = plane.elevation_at_low_coord;
      ebr = etr = plane.elevation_at_high_coord;
      float cl = 255 * (etl - gradient_start) / gradient_factor;
      float cr = 255 * (ebr - gradient_start) / gradient_factor;
      ctl = cbl = NSEngine::Color(cl, cl, cl, 255);
      ctr = cbr = NSEngine::Color(cr, cr, cr, 255);
    } else if (plane.slope_type == PlaneSlopeType::Z_VARIES) {
      etl = etr = plane.elevation_at_low_coord;
      ebr = ebl = plane.elevation_at_high_coord;
      float ct = 255 * (etl - gradient_start) / gradient_factor;
      float cb = 255 * (ebl - gradient_start) / gradient_factor;
      ctl = ctr = NSEngine::Color(ct, ct, ct, 255);
      cbl = cbr = NSEngine::Color(cb, cb, cb, 255);
    } else {
      etl = etr = ebr = ebl = plane.elevation_at_high_coord;
      float c = 255 * (etl - gradient_start) / gradient_factor;
      ctl = ctr = cbl = cbr = NSEngine::Color(c, c, c, 255);
    }
    float x1 = plane.coord_low.x;
    float z1 = plane.coord_low.y;
    float x2 = plane.coord_high.x;
    float z2 = plane.coord_high.y;
    NSEngine::draw_quad_color({x1, etl, z1}, {x2, etr, z1}, {x2, ebr, z2},
                              {x1, ebl, z2}, ctl, ctr, cbr, cbl);
  }
}

bool RoomCollider::Plane::is_on(float x, float z) const {
  return x >= coord_low.x && x <= coord_high.x && z >= coord_low.y &&
         z <= coord_high.y;
}

bool RoomCollider::Plane::should_go_to(Plane const &p2, glm::vec2 prev,
                                       glm::vec2 now) const {
  float y_prev = elevation(prev.x, prev.y);
  float y2_prev = p2.elevation(prev.x, prev.y);
  float y = elevation(now.x, now.y);
  float y2 = p2.elevation(now.x, now.y);
  return ((y_prev - y2_prev) * (y - y2)) <= 0;
}

float RoomCollider::Plane::elevation(float x, float z) const {
  if (slope_type == PlaneSlopeType::X_VARIES) {
    float fact =
        math::clamp((x - coord_low.x) / (coord_high.x - coord_low.x), 0.f, 1.f);
    return elevation_at_low_coord +
           fact * (elevation_at_high_coord - elevation_at_low_coord);
  } else if (slope_type == PlaneSlopeType::Z_VARIES) {
    float fact =
        math::clamp((z - coord_low.y) / (coord_high.y - coord_low.y), 0.f, 1.f);
    return elevation_at_low_coord +
           fact * (elevation_at_high_coord - elevation_at_low_coord);
  } else {
    return elevation_at_low_coord;
  }
}

std::vector<size_t> RoomCollider::get_intersection_planes(float x,
                                                          float z) const {
  std::vector<size_t> ret;
  size_t i = 0;
  for (auto const &p : m_planes) {
    if (p.is_on(x, z)) {
      ret.push_back(i);
    }
    i++;
  }
  return ret;
}

bool segment_intersect(glm::vec2 p, glm::vec2 p2, glm::vec2 q, glm::vec2 q2,
                       float &inter_x, float &inter_y) {
  glm::vec2 r = p2 - p;
  glm::vec2 s = q2 - q;

  auto rts = r.x * s.y - r.y * s.x;
  if (rts == 0)
    return false;

  auto rnorm = glm::vec2(r.y, -r.x);
  auto dot = rnorm.x * s.x + rnorm.y * s.y;
  if (dot < 0)
    return false;

  auto qmp = q - p;
  auto qmpts = qmp.x * s.y - qmp.y * s.x;
  auto qmptr = qmp.x * r.y - qmp.y * r.x;
  auto t = qmpts / rts;
  auto u = qmptr / rts;

  if (0 <= t && t <= 1 && 0 <= u && u <= 1) {
    auto pt = p + t * r;
    inter_x = pt.x;
    inter_y = pt.y;
    return true;
  } else {
    return false;
  }
}

void RoomCollider::wallcheck(float &x, float y, float &z, float xp,
                             float zp) const {
  for (auto const &w : m_walls) {
    if (y < w.elevation_low || y > w.elevation_high)
      continue;
    float ix, iz;
    if (segment_intersect(w.point_xz_1, w.point_xz_2, {xp, zp}, {x, z}, ix,
                          iz)) {
      x = ix;
      z = iz;
    }
  }
}
