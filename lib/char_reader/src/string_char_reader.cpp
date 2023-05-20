#include "string_char_reader.hpp"

#include <sstream>

// TODO(affeeal): избавиться от дублирования функциональности
// классов StringCharReader и StringCharReader
StringCharReader::StringCharReader(std::stringstream&& ss)
  : ss_(std::move(ss)) {
}

// по умолчанию k = 0
char StringCharReader::Peek(std::size_t k) {
  auto pos = ss_.tellg();
  ss_.seekg(k, ss_.cur);
  char ch = ss_.peek();
  ss_.seekg(pos);
  return ch;
}

// по умолчанию k = 0
char StringCharReader::Get(std::size_t k) {
  ss_.seekg(k, ss_.cur);
  return ss_.get();
}

bool StringCharReader::IsEof() {
  return (ss_.rdbuf()->in_avail() == 0);
}

void StringCharReader::set_ss(std::stringstream&& ss) {
  ss_ = std::move(ss);
}
