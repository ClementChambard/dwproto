#include "./DataReader.hpp"

void DataReader::skip(size_t n) { cursor += n; }
uint8_t DataReader::u8() {
  uint8_t d = *cursor;
  cursor += sizeof(uint8_t);
  len_remaining -= sizeof(uint8_t);
  return d;
}
int8_t DataReader::i8() {
  int8_t d = *reinterpret_cast<int8_t *>(cursor);
  cursor += sizeof(int8_t);
  len_remaining -= sizeof(int8_t);
  return d;
}
uint16_t DataReader::u16() {
  uint16_t d = *reinterpret_cast<uint16_t *>(cursor);
  cursor += sizeof(uint16_t);
  len_remaining -= sizeof(uint16_t);
  return d;
}
int16_t DataReader::i16() {
  int16_t d = *reinterpret_cast<int16_t *>(cursor);
  cursor += sizeof(int16_t);
  len_remaining -= sizeof(int16_t);
  return d;
}
uint32_t DataReader::u32() {
  uint32_t d = *reinterpret_cast<uint32_t *>(cursor);
  cursor += sizeof(uint32_t);
  len_remaining -= sizeof(uint32_t);
  return d;
}
int32_t DataReader::i32() {
  int32_t d = *reinterpret_cast<int32_t *>(cursor);
  cursor += sizeof(int32_t);
  len_remaining -= sizeof(int32_t);
  return d;
}
uint64_t DataReader::u64() {
  uint64_t d = *reinterpret_cast<uint64_t *>(cursor);
  cursor += sizeof(uint64_t);
  len_remaining -= sizeof(uint64_t);
  return d;
}
int64_t DataReader::i64() {
  int64_t d = *reinterpret_cast<int64_t *>(cursor);
  cursor += sizeof(int64_t);
  len_remaining -= sizeof(int64_t);
  return d;
}

float DataReader::f32() {
  float d = *reinterpret_cast<float *>(cursor);
  cursor += sizeof(float);
  len_remaining -= sizeof(float);
  return d;
}
double DataReader::f64() {
  double d = *reinterpret_cast<double *>(cursor);
  cursor += sizeof(double);
  len_remaining -= sizeof(double);
  return d;
}

glm::vec2 DataReader::v2() { return {f32(), f32()}; }
glm::vec3 DataReader::v3() { return {f32(), f32(), f32()}; }
glm::vec4 DataReader::v4() { return {f32(), f32(), f32(), f32()}; }

uint8_t *DataReader::offset() { return cursor + i32(); }

bool DataReader::eof() const { return len_remaining == 0; }
