#include "IstreamReader.hpp"

#include <istream>
#include <memory>

namespace reader {
IstreamReader::IstreamReader()
    : source_(nullptr) {
}

IstreamReader::IstreamReader(std::unique_ptr<std::istream>&& source)
  : source_(std::move(source)) {
}

// по умолчанию k = 0
char IstreamReader::Peek(std::size_t k) {
  std::streambuf::pos_type position = source_->tellg();
  source_->seekg(k, source_->cur);
  char character = source_->peek();
  source_->seekg(position);
  return character;
}

// по умолчанию k = 0
char IstreamReader::Get(std::size_t k) {
  source_->seekg(k, source_->cur);
  return source_->get();
}

bool IstreamReader::IsEof() {
  return !source_->rdbuf()->in_avail();
}

void IstreamReader::set_source(std::unique_ptr<std::istream>&& source) {
  source_ = std::move(source);
}
} // namespace reader
