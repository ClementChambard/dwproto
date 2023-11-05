#ifndef DATAREADER_INCLUDED_H
#define DATAREADER_INCLUDED_H

#include <cstddef>
#include <cstdint>
#include <glm/glm.hpp>

class DataReader {
public:
  DataReader(uint8_t *data, size_t len)
      : data(data), cursor(data), data_len(len), len_remaining(len) {}

  void skip(size_t n);
  uint8_t u8();
  int8_t i8();
  uint16_t u16();
  int16_t i16();
  uint32_t u32();
  int32_t i32();
  uint64_t u64();
  int64_t i64();
  glm::vec2 v2();
  glm::vec3 v3();
  glm::vec4 v4();
  uint8_t *offset();

  float f32();
  double f64();

  bool eof() const;

private:
  uint8_t *data;
  uint8_t *cursor;
  size_t data_len;
  size_t len_remaining;
};

#endif // !DATAREADER_INCLUDED_H
