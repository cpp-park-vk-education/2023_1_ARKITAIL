#include "character_reader.hpp"

FileCharacterReader::FileCharacterReader(std::ifstream&& f)
  : f_(std::move(f)) {
}

char FileCharacterReader::Peek(std::size_t k) {
  auto pos = f_.tellg();
  f_.seekg(k, f_.cur);
  char ch = f_.peek();
  f_.seekg(pos);
  return ch;
}

char FileCharacterReader::Get(std::size_t k) {
  f_.seekg(k, f_.cur);
  return f_.get();
}

bool FileCharacterReader::IsEof() {
  return f_.peek() == std::string::npos;
}
