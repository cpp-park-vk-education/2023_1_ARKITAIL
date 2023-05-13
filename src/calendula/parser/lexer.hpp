#pragma once

#include <string>

#include "character_reader.hpp"

enum class Tag {
  kBof,

  kDelimiter,
  kIdentifier,

  kEof,
};

struct Lexem {
  Tag tag;
  std::string image;

  explicit Lexem(Tag tag) : tag(tag), image(std::string()) {
  }

  Lexem(Tag tag, std::string&& image) : tag(tag), image(std::move(image)) {
  }
  
  bool operator==(const Lexem& other) const {
    return tag == other.tag && image == other.image;
  }
};

class ILexer {
 public:
  virtual Lexem Get() = 0;
  virtual Lexem Peek() = 0;
  
  virtual ~ILexer() = default;
};

class iCalendarLexer : public ILexer {
 public:
  iCalendarLexer() : character_reader_(nullptr), current_(Lexem(Tag::kBof)) {
  }

  Lexem Get() override;
  Lexem Peek() override;

  void set_character_reader(ICharacterReader& character_reader);
 private:
  Lexem GetInternal();
  Lexem GetIdentificator();
  bool IsDelimiter(char character) const;
  
  ICharacterReader* character_reader_;
  Lexem current_;
};
