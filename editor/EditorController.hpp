#ifndef EDITORCONTROLLER_INCLUDED_H
#define EDITORCONTROLLER_INCLUDED_H

/* interface */ class EditorController {
public:
  virtual ~EditorController() {}

  virtual bool wantsControls() { return false; }
  virtual void helperImGui() {}
  virtual void onTickGlobal(EditorController * /* currentController */) {}
  virtual void onTickControlled() {}
  virtual void onDrawGlobal(EditorController * /* currentController */) {}
  virtual void onDrawControlled() {}
};

#endif // !EDITORCONTROLLER_INCLUDED_H
