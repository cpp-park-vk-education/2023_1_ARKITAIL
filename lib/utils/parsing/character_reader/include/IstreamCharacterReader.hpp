#pragma once

#include <istream>
#include <streambuf>

#include "ICharacterReader.hpp"
#include "IStreamBuffer.hpp"

namespace parsing {
class IstreamCharacterReader : public ICharacterReader,
                               public IStreamBuffer,
                               protected std::istream {
 public:
  IstreamCharacterReader() = default;
  explicit IstreamCharacterReader(std::streambuf* rdbuf);

  // методы ICharacterReader
  virtual char Peek(std::size_t k = 0) override;
  virtual char Get(std::size_t k = 0) override;
  virtual bool IsEof() override;

  // методы IStreamBuffer
  virtual void SetBuffer(std::streambuf* buffer) override;
  virtual std::streambuf* Buffer() override;
};
} // namespace parsing
