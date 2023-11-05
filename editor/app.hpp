#ifndef APP_INCLUDED_H
#define APP_INCLUDED_H

#include "./editor.hpp"
#include <Engine.hpp>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class App : public NSEngine::IEngine {
public:
  App(int argc, char **argv)
      : IEngine(WINDOW_WIDTH, WINDOW_HEIGHT, "dw edit"), m_argc(argc),
        m_argv(argv) {}
  ~App() override {}

  void on_create() override;
  void on_update() override;
  void on_render() override;
  void on_destroy() override;

private:
  int m_argc = 0;
  char **m_argv = nullptr;

  Editor editor{};
};

#endif // !APP_INCLUDED_H
