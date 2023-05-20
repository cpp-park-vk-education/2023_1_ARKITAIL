#include "FileCharacterReader.hpp"

#include <fstream>

// TODO(affeeal): избавиться от дублирования функциональности
// классов StringCharReader и StringCharReader
FileCharacterReader::FileCharacterReader(std::ifstream&& fs)
  : fs_(std::move(fs)) {
}

// по умолчанию k = 0
char FileCharacterReader::Peek(std::size_t k) {
  auto pos = fs_.tellg();
  fs_.seekg(k, fs_.cur);
  char ch = fs_.peek();
  fs_.seekg(pos);
  return ch;
}

// по умолчанию k = 0
char FileCharacterReader::Get(std::size_t k) {
  fs_.seekg(k, fs_.cur);
  return fs_.get();
}

bool FileCharacterReader::IsEof() {
  return (fs_.rdbuf()->in_avail() == 0);
}

void FileCharacterReader::set_fs(std::ifstream&& fs) {
  fs_ = std::move(fs);
}
