#include "./Controllers.hpp"

Controllers::Controllers() { controllers.push_back(&m_camera); }

#include <iostream>

void Controllers::onTick() {
  bool someone_has_control = m_current && m_current->wantsControls();
  if (!someone_has_control) {
    m_current = nullptr;
    for (auto c : controllers) {
      if (c->wantsControls()) {
        m_current = c;
        break;
      }
    }
  }

  for (auto c : controllers) {
    c->onTickGlobal(m_current);
  }
  if (m_current)
    m_current->onTickControlled();
}

void Controllers::onDraw() {
  for (auto c : controllers) {
    c->onDrawGlobal(m_current);
  }
  if (m_current)
    m_current->onDrawControlled();
}

void Controllers::imguiHelp() {
  if (m_current)
    m_current->helperImGui();
}
