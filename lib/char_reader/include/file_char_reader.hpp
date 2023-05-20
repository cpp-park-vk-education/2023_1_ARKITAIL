#pragma once

#include <cstddef>
#include <fstream>

#include "i_char_reader.hpp"

class FileCharReader : public ICharReader {
 public:
  FileCharReader() = default;
  explicit FileCharReader(std::ifstream&& fs);

  char Peek(std::size_t k = 0) override;
  char Get(std::size_t k = 0) override;
  bool IsEof() override;
  
  void set_fs(std::ifstream&& fs);
 private:
  std::ifstream fs_;
};
