#ifndef EDITOR_INCLUDED_H
#define EDITOR_INCLUDED_H

#include "./Controllers.hpp"

class Editor {
public:
  ~Editor();
  void init();
  void on_tick();
  void on_draw();

  Controllers controllers;
};

#endif // !EDITOR_INCLUDED_H
