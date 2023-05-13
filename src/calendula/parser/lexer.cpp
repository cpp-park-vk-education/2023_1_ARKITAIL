#include "lexer.hpp"

#include <algorithm>
#include <array>

const std::size_t kDelimitersSize = 5;
const std::array<char, kDelimitersSize> kDelimiters { 
  ':',
  '\n',
  '\r',
  ';',
  '='
};

Lexem iCalendarLexer::Get() {
  Lexem current = (current_.tag == Tag::kBof) ? GetInternal()
                                              : std::move(current_);
  current_ = GetInternal();
  return current;
}

Lexem iCalendarLexer::Peek() {
  return (current_.tag == Tag::kBof) ? current_ = GetInternal() 
                                     : current_;
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

void iCalendarLexer::set_character_reader(ICharacterReader& character_reader) {
  character_reader_ = &character_reader;
}
