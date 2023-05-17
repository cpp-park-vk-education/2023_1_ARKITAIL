#pragma once

#include <cstddef>
#include <fstream>

#include "i_char_reader.hpp"

class FileCharReader : public ICharReader {
 public:
  explicit FileCharReader(std::ifstream&& fs);

  char Peek(std::size_t k = 0) override;
  char Get(std::size_t k = 0) override;
  bool IsEof() override;
  
 private:
  std::ifstream fs_;
};
