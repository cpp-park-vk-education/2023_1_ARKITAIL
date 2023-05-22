#include "IstreamCharacterReader.hpp"

#include <istream>
#include <streambuf>

namespace parsing {
IstreamCharacterReader::IstreamCharacterReader(std::streambuf* rdbuf)
  : std::istream(rdbuf) {
}

// по умолчанию k = 0
char IstreamCharacterReader::Peek(std::size_t k) {
  auto pos = tellg();
  seekg(k, cur);
  char ch = peek();
  seekg(pos);
  return ch;
}

// по умолчанию k = 0
char IstreamCharacterReader::Get(std::size_t k) {
  seekg(k, cur);
  return get();
}

bool IstreamCharacterReader::IsEof() {
  return (rdbuf()->in_avail() == 0);
}

void IstreamCharacterReader::SetBuffer(std::streambuf* buffer) {
  set_rdbuf(buffer);
}

std::streambuf* IstreamCharacterReader::Buffer() {
  return rdbuf();
}
} // namespace parsing
