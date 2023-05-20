#pragma once

#include <cstddef>
#include <fstream>

#include "ICharacterReader.hpp"

class FileCharacterReader : public ICharReader {
 public:
  FileCharacterReader() = default;
  explicit FileCharacterReader(std::ifstream&& fs);

  char Peek(std::size_t k = 0) override;
  char Get(std::size_t k = 0) override;
  bool IsEof() override;
  
  void set_fs(std::ifstream&& fs);
 private:
  std::ifstream fs_;
};
