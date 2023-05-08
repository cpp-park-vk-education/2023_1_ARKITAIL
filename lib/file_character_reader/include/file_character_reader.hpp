#pragma once

#include <fstream>
#include <string>

#include "i_character_reader.hpp"

class FileCharacterReader : public ICharacterReader {
 public:
  explicit FileCharacterReader(std::ifstream&& f);

  char Peek() override;
  char Get() override;
  bool IsEOF() const override;
  
 private:
  std::ifstream f_;
};
