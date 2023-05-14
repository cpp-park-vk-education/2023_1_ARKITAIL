#include "lexer.hpp"

#include <algorithm>
#include <array>
#include <deque>

const std::size_t kDelimitersSize = 5;
const std::array<char, kDelimitersSize> kDelimiters { 
  ':',
  '\n',
  '\r',
  ';',
  '='
};

const Lexem kEof(Tag::kEof);

const Lexem kBegin(Tag::kIdentifier, "BEGIN");
const Lexem kEnd(Tag::kIdentifier, "END");

const Lexem kColon(Tag::kDelimiter, ":");
const Lexem kSemicolon(Tag::kDelimiter, ";");
const Lexem kEqual(Tag::kDelimiter, "=");
const Lexem kCarriageReturn(Tag::kDelimiter, "\r");
const Lexem kLineFeed(Tag::kDelimiter, "\n");

// выбрасывает (k+1) лексему и возвращает k-ю
// по умолчанию k = 0
Lexem iCalendarLexer::Get(std::size_t k) {
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
Lexem iCalendarLexer::Peek(std::size_t k) {
  if (got_lexems_.size() <= k) {
    PushLacking(k - got_lexems_.size() + 1);
  }

  return got_lexems_[k];
}

void iCalendarLexer::PushLacking(std::size_t k) {
  for (std::size_t i = 0; i < k; i++) {
    got_lexems_.push_back(GetInternal());
  }
}

Lexem iCalendarLexer::GetInternal() {
  if (character_reader_->IsEof()) {
    return Lexem(Tag::kEof);
  }

  char curr_char = character_reader_->Peek();

  // Символ - разделитель
  if (IsDelimiter(curr_char)) {
    character_reader_->Get();
    return Lexem(Tag::kDelimiter, std::string(1, curr_char));
  }

  // Символ - идентификатор
  return GetIdentificator();
}

Lexem iCalendarLexer::GetIdentificator() {
  std::string result = "";

  while (!character_reader_->IsEof()
      && !IsDelimiter(character_reader_->Peek())) {
    result += character_reader_->Get();
  }

  return Lexem(Tag::kIdentifier, std::move(result));
}

bool iCalendarLexer::IsDelimiter(char character) const {
  return (std::find(std::begin(kDelimiters), std::end(kDelimiters), character)
          != kDelimiters.end());
}

void iCalendarLexer::set_character_reader(ICharReader& character_reader) {
  character_reader_ = &character_reader;
}
