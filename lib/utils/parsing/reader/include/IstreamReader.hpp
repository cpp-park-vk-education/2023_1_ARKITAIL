#pragma once

#include <istream>
#include <memory>

#include "IReader.hpp"

namespace reader {
class IstreamReader : public IReader {
 public:
  IstreamReader();
  explicit IstreamReader(std::unique_ptr<std::istream>&& source);

  // методы IReader
  virtual char Peek(std::size_t k = 0) override;
  virtual char Get(std::size_t k = 0) override;
  virtual bool IsEof() override;

  void set_source(std::unique_ptr<std::istream>&& source);
 private:
  std::unique_ptr<std::istream> source_;
};
} // namespace reader
