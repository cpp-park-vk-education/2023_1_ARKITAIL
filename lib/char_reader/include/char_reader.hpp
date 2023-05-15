#pragma once

#include <cstddef>
#include <fstream>

class ICharReader {
 public:
  virtual char Peek(std::size_t k = 0) = 0;
  virtual char Get(std::size_t k = 0) = 0;

  virtual bool IsEof() = 0;

  virtual ~ICharReader() = default;
};

class FileCharReader : public ICharReader {
 public:
  explicit FileCharReader(std::ifstream&& fs);

  char Peek(std::size_t k = 0) override;
  char Get(std::size_t k = 0) override;

  bool IsEof() override;
  
 private:
  std::ifstream fs_;
};
