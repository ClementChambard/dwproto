#include "./App.hpp"
#include "./Player.hpp"
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
}

void App::on_update() {
  // TODO: UPDATE_FUNC_REGISTRY System
  CURRENT_AREA->on_tick();
  PLAYER_PTR->on_tick_debug();
}

void App::on_render() {
  CURRENT_AREA->on_draw();
  PLAYER_PTR->on_draw_debug();
}

void App::on_destroy() {}
