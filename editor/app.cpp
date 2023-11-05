#include "./app.hpp"
#include <NSEngine.h>

void App::on_create() {
  setMaxFps(60);
  NSEngine::createCamera(NS_CAM_3D, WINDOW_WIDTH, WINDOW_HEIGHT);
  editor.init();
}

void App::on_update() { editor.on_tick(); }

void App::on_render() { editor.on_draw(); }

void App::on_destroy() {}
