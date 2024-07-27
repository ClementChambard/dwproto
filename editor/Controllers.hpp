#ifndef CONTROLLERS_INCLUDED_H
#define CONTROLLERS_INCLUDED_H

#include "./EditorCamera.hpp"
#include "./EditorController.hpp"

#include <vector>

class Controllers {
public:
  Controllers();
  std::vector<EditorController *> controllers{};

  void onTick();
  void onDraw();
  void imguiHelp();

private:
  EditorCamera m_camera{};
  EditorController *m_current = nullptr;
};

#endif // !CONTROLLERS_INCLUDED_H
