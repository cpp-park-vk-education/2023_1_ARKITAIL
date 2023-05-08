#include "file_character_reader.hpp"

#include <fstream>

FileCharacterReader::FileCharacterReader(std::ifstream&& f)
  : f_(std::move(f)) {}

char FileCharacterReader::Peek() {
  return f_.peek();
}

char FileCharacterReader::Get() {
  return f_.get();
}

bool FileCharacterReader::IsEOF() const {
  return f_.eof();
}
