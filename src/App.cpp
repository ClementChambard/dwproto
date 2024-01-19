#include "./App.hpp"
#include "./Player.hpp"
#include "./Camera.hpp"
#include "world/Area.hpp"
#include <FrameBuffer.h>
#include <GL/glew.h>
#include <NSEngine.h>
#include <glm/common.hpp>
#include <glm/fwd.hpp>
#include <vector>

void App::on_create() {
  NSEngine::createCamera(NS_CAM_3D, WINDOW_WIDTH, WINDOW_HEIGHT);
  NSEngine::addGameLayer(true);
  (new Area())->testEnv();
  new Player();
  new Camera();
}

void App::on_update() {
  // TODO: UPDATE_FUNC_REGISTRY System
  CURRENT_AREA->on_tick();
  Player::INSTANCE->on_tick_debug();
  Camera::INSTANCE->on_tick();
}

void App::on_render() {
  CURRENT_AREA->on_draw();
  Player::INSTANCE->on_draw_debug();
}

void App::on_destroy() {}
