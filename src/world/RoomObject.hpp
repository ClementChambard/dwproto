#ifndef ROOMOBJECT_INCLUDED_H
#define ROOMOBJECT_INCLUDED_H

#include "./RoomEvent.hpp"

class RoomObject {
public:
  virtual ~RoomObject() {}

  virtual void on_tick() = 0;
  virtual void on_draw() = 0;
  virtual void on_room_event(RoomEvent *) {}
};

#endif // !ROOMOBJECT_INCLUDED_H
