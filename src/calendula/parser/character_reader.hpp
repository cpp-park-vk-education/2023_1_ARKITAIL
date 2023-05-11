#pragma once

#include <cstddef>
#include <fstream>

class ICharacterReader {
 public:
  virtual char Peek(std::size_t k = 0) = 0;
  virtual char Get(std::size_t k = 0) = 0;

  virtual bool IsEof() = 0;

  virtual ~ICharacterReader() = default;
};

class FileCharacterReader : public ICharacterReader {
 public:
  explicit FileCharacterReader(std::ifstream&& f);

  char Peek(std::size_t k = 0) override;
  char Get(std::size_t k = 0) override;

  bool IsEof() override;
  
 private:
  std::ifstream f_;
};
