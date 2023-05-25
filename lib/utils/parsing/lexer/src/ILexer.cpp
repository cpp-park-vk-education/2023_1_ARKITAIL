#include "ILexer.hpp"

#include <string>

namespace lexer {
const Lexem kEof(Tag::kEof);
const Lexem kBegin(Tag::kIdentifier, "BEGIN");
const Lexem kEnd(Tag::kIdentifier, "END");
const Lexem kColon(Tag::kDelimiter, ":");
const Lexem kSemicolon(Tag::kDelimiter, ";");
const Lexem kEqual(Tag::kDelimiter, "=");
const Lexem kCarriageReturn(Tag::kDelimiter, "\r");
const Lexem kLineFeed(Tag::kDelimiter, "\n");

Lexem::Lexem(Tag tag)
    : tag(tag), image(std::string()) {
}

Lexem::Lexem(Tag tag, const std::string& image)
    : tag(tag), image(image) {
}

bool Lexem::operator==(const Lexem& other) const {
  return tag == other.tag && image == other.image;
}

bool Lexem::operator!=(const Lexem& other) const {
  return tag != other.tag || image != other.image;
}
} // namespace lexer
