#include "file_char_reader.hpp"

#include <fstream>

// TODO(affeeal): избавиться от дублирования функциональности
// классов StringCharReader и StringCharReader
FileCharReader::FileCharReader(std::ifstream&& fs)
  : fs_(std::move(fs)) {
}

// по умолчанию k = 0
char FileCharReader::Peek(std::size_t k) {
  auto pos = fs_.tellg();
  fs_.seekg(k, fs_.cur);
  char ch = fs_.peek();
  fs_.seekg(pos);
  return ch;
}

// по умолчанию k = 0
char FileCharReader::Get(std::size_t k) {
  fs_.seekg(k, fs_.cur);
  return fs_.get();
}

bool FileCharReader::IsEof() {
  return (fs_.rdbuf()->in_avail() == 0);
}

void FileCharReader::set_fs(std::ifstream&& fs) {
  fs_ = std::move(fs);
}
