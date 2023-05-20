#pragma once

#include <cstddef>
#include <sstream>

#include "ICharacterReader.hpp"

class StringCharacterReader : public ICharReader {
 public:
  StringCharacterReader() = default;
  explicit StringCharacterReader(std::stringstream&& ss);

  char Peek(std::size_t k = 0) override;
  char Get(std::size_t k = 0) override;
  bool IsEof() override;

  void set_ss(std::stringstream&& ss);
 private:
  std::stringstream ss_;
};
