#ifndef ROOMEVENT_INCLUDED_H
#define ROOMEVENT_INCLUDED_H

enum class RoomEventKind {
  ROOM_ENTERED,
  ROOM_LEFT,
};

struct RoomEvent {
  RoomEventKind kind;
  union {
    struct {
      int a;
    } dataEvent;
    struct {
      float b;
    } anotherDataEvent;
  } event;
};

#endif // !ROOMEVENT_INCLUDED_H
