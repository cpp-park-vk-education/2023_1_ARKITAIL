#pragma once

#include <string>

#include "IReader.hpp"

namespace lexer {
enum class Tag;
struct Lexem;
class ILexer;

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

  explicit Lexem(Tag tag);
  Lexem(Tag tag, const std::string& image);
  
  bool operator==(const Lexem& other) const;
  bool operator!=(const Lexem& other) const;
};

class ILexer {
 public:
  virtual Lexem Get(std::size_t k = 0) = 0;
  virtual Lexem Peek(std::size_t k = 0) = 0;
  
  virtual ~ILexer() = default;
};
} // namespace lexer
