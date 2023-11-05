#ifndef EDITOR_INCLUDED_H
#define EDITOR_INCLUDED_H

class Editor {
public:
  ~Editor();
  void init();
  void on_tick();
  void on_draw();
};

#endif // !EDITOR_INCLUDED_H
