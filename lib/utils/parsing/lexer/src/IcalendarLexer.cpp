#include "IcalendarLexer.hpp"

#include <algorithm>
#include <array>

#include "IReader.hpp"

namespace lexer {
const std::size_t kDelimitersSize = 5;
const std::array<char, kDelimitersSize> kDelimiters { 
  ':',
  '\n',
  '\r',
  ';',
  '='
};

// выбрасывает (k+1) лексему и возвращает k-ю
// по умолчанию k = 0
Lexem IcalendarLexer::Get(std::size_t k) {
  if (got_lexems_.size() <= k) {
    PushLacking(k - got_lexems_.size() + 1);
  }

  Lexem current = got_lexems_[k];

  for (std::size_t i = 0; i <= k; i++) {
    got_lexems_.pop_front();
  }

  return current;
}

// подглядывает за k-й лексемой
// по умолчанию k = 0
Lexem IcalendarLexer::Peek(std::size_t k) {
  if (got_lexems_.size() <= k) {
    PushLacking(k - got_lexems_.size() + 1);
  }

  return got_lexems_[k];
}

void IcalendarLexer::PushLacking(std::size_t k) {
  for (std::size_t i = 0; i < k; i++) {
    got_lexems_.push_back(GetInternal());
  }
}

Lexem IcalendarLexer::GetInternal() {
  if (reader_->IsEof()) {
    return Lexem(Tag::kEof);
  }

  char current = reader_->Peek();

  // Символ - разделитель
  if (IsDelimiter(current)) {
    reader_->Get();
    return Lexem(Tag::kDelimiter, std::string(1, current));
  }

  // Символ - идентификатор
  return GetIdentificator();
}

Lexem IcalendarLexer::GetIdentificator() {
  std::string result = "";

  while (!reader_->IsEof() && !IsDelimiter(reader_->Peek())) {
    result += reader_->Get();
  }

  return Lexem(Tag::kIdentifier, std::move(result));
}

bool IcalendarLexer::IsDelimiter(char character) const {
  return (std::find(std::begin(kDelimiters), std::end(kDelimiters), character)
          != kDelimiters.end());
}

void IcalendarLexer::set_reader(reader::IReader& reader) {
  reader_ = &reader;
}
} // namespace parsing
