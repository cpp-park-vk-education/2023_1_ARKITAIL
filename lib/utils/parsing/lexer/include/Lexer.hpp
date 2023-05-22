#pragma once

#include <deque>
#include <string>

#include "ICharacterReader.hpp"

namespace parsing {
enum class Tag;

struct Lexem;

class ILexer;
class IcalendarLexer;

extern const Lexem kEof;

extern const Lexem kBegin;
extern const Lexem kEnd;

extern const Lexem kColon;
extern const Lexem kSemicolon;
extern const Lexem kEqual;
extern const Lexem kCarriageReturn;
extern const Lexem kLineFeed;

enum class Tag {
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

  bool operator!=(const Lexem& other) const {
    return tag != other.tag || image != other.image;
  }
};

class ILexer {
 public:
  virtual Lexem Get(std::size_t k = 0) = 0;
  virtual Lexem Peek(std::size_t k = 0) = 0;
  
  virtual ~ILexer() = default;
};

class IcalendarLexer : public ILexer {
 public:
  IcalendarLexer() : character_reader_(nullptr) {
  }

  Lexem Get(std::size_t k = 0) override;
  Lexem Peek(std::size_t k = 0) override;

  void set_character_reader(ICharacterReader& character_reader);
 private:
  Lexem GetInternal();
  Lexem GetIdentificator();

  void PushLacking(std::size_t k);
  bool IsDelimiter(char character) const;
  
  ICharacterReader* character_reader_;
  std::deque<Lexem> got_lexems_;
};
} // namespace parsing
