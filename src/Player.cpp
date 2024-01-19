#include "./Player.hpp"
#include "Camera.hpp"
#include "world/Area.hpp"
#include <NSEngine.h>
#include <glm/ext/scalar_constants.hpp>

Player *Player::INSTANCE = nullptr;

Player::Player() {
  // todo do this properly
  if (INSTANCE)
    delete INSTANCE;
  INSTANCE = this;
}

Player::~Player() { INSTANCE = nullptr; }

void Player::on_tick_debug() {
  // camera

  static float vy = 0.f;
  // static float pitch = 0;
  // static float yaw = 0;
  // static float mouseSpeed = 0.02;
  // static float moveSpeed = 3;
  // static glm::vec3 camPos = NSEngine::camPos();
  // static auto look = NSEngine::activeCamera3D()->getLook();
  //
  // yaw -= mouseSpeed * Inputs::Keyboard().Axis(NSK_q, NSK_e);
  // pitch += mouseSpeed * Inputs::Keyboard().Axis(NSK_f, NSK_r);
  // pitch = glm::clamp(pitch, -PI / 2.f + 0.001f, PI / 2.f - 0.001f);
  // float keyHoriz = moveSpeed * Inputs::Keyboard().Axis(NSK_d, NSK_a);
  // float keyVerti = moveSpeed * Inputs::Keyboard().Axis(NSK_s, NSK_w);
  // look = glm::vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
  // float dbgx = camPos.x + keyHoriz * cos(yaw) + keyVerti * sin(yaw);
  // float dbgz = camPos.z + -keyHoriz * sin(yaw) + keyVerti * cos(yaw);
  // float dbgy =
  //     camPos.y + moveSpeed * Inputs::Keyboard().Axis(NSK_lshift, NSK_space);
  // camPos = glm::vec3(dbgx, dbgy, dbgz);
  //
  // NSEngine::activeCamera3D()->setPosition(camPos.x, camPos.y, camPos.z);
  // NSEngine::activeCamera3D()->setLook(look.x, look.y, look.z);

  float yaw = 0.0;
  if (Camera::INSTANCE) {
    yaw = Camera::INSTANCE->yaw + glm::pi<float>();
  }

  // player
  auto forward = glm::normalize(glm::vec2(cos(yaw), sin(yaw)));
  auto right = glm::vec2(-forward.y, forward.x);

  if (Inputs::Keyboard().Down(NSK_left)) {
    collider.inc_pos({-right.x, 0, -right.y});
  }
  if (Inputs::Keyboard().Down(NSK_right)) {
    collider.inc_pos({right.x, 0, right.y});
  }
  if (Inputs::Keyboard().Down(NSK_up)) {
    collider.inc_pos({forward.x, 0, forward.y});
  }
  if (Inputs::Keyboard().Down(NSK_down)) {
    collider.inc_pos({-forward.x, 0, -forward.y});
  }
  if (Inputs::Keyboard().Down(NSK_space)) {
    vy = 3;
  }
  if (!collider.on_ground())
    vy -= 0.1;
  if (vy < -5)
    vy = -5;
  collider.inc_pos({0, vy, 0});
  CURRENT_AREA->resolveCollisions(collider);
  if (collider.on_ground())
    vy = 0;
}

void Player::on_draw_debug() {
  auto col = collider.on_ground() ? c_blue : c_red;
  NSEngine::draw_billboard(collider.pos(), {8, 8}, 1, {0, 0, 0, 0}, col, col,
                           col, col);
}
