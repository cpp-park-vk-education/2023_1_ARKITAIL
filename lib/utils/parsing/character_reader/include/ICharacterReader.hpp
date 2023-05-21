#pragma once

#include <cstddef>

class ICharacterReader {
 public:
  virtual char Peek(std::size_t k = 0) = 0;
  virtual char Get(std::size_t k = 0) = 0;
  virtual bool IsEof() = 0;

  virtual ~ICharacterReader() = default;
};
