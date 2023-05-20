#pragma once

#include <cstddef>
#include <sstream>

#include "i_char_reader.hpp"

class StringCharReader : public ICharReader {
 public:
  StringCharReader() = default;
  explicit StringCharReader(std::stringstream&& ss);

  char Peek(std::size_t k = 0) override;
  char Get(std::size_t k = 0) override;
  bool IsEof() override;

  void set_ss(std::stringstream&& ss);
 private:
  std::stringstream ss_;
};
