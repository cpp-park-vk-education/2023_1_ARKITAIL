#pragma once

#include <deque>
#include <string>

#include "ILexer.hpp"
#include "IReader.hpp"

namespace lexer {
class IcalendarLexer : public ILexer {
 public:
  IcalendarLexer() = default;

  Lexem Get(std::size_t k = 0) override;
  Lexem Peek(std::size_t k = 0) override;

  void set_reader(reader::IReader& reader);
 private:
  Lexem GetInternal();
  Lexem GetIdentificator();
  void PushLacking(std::size_t k);
  bool IsDelimiter(char character) const;
  
  reader::IReader* reader_;
  std::deque<Lexem> got_lexems_;
};
} // namespace lexer
