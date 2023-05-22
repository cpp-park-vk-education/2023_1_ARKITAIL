#pragma once

#include <streambuf>

namespace parsing {
class IStreamBuffer {
 public:
  virtual void SetBuffer(std::streambuf* buffer) = 0;
  virtual std::streambuf* Buffer() = 0;

  virtual ~IStreamBuffer() = default;
};
} // namespace parsing
