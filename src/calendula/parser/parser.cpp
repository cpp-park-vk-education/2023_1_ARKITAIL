#include "parser.hpp"

#include <memory>

#include "lexer.hpp"

/*
stream         = *component

               ; нетерминалы name в данной
               ; component должны представлять
               ; одно и то же значение
component      = "BEGIN" ":" name "\r" "\n"
                 *property
                 *component
                 "END" ":" name "\r" "\n"

property       = name *parameter ":" property-value "\r" "\n"
   
               ; TODO: случай с 
               ; несколькими значениями
parameter      = ";" pair-value

property-value = value / ( pair-value *( ";" pair-value ) )

name           = *( ALPHA / "-" )

pair-value     = name "=" value

value          = любые символы, за исключением ";", "=" и "\r"
*/

const Lexem kEof(Tag::kEof);

const Lexem kBegin(Tag::kIdentifier, "BEGIN");
const Lexem kEnd(Tag::kIdentifier, "END");

const Lexem kColon(Tag::kDelimiter, ":");
const Lexem kSemicolon(Tag::kDelimiter, ";");
const Lexem kEqual(Tag::kDelimiter, "=");
const Lexem kCarriageReturn(Tag::kDelimiter, "\r");
const Lexem kLineFeed(Tag::kDelimiter, "\n");

void iCalendarParser::set_lexer(ILexer &lexer) {
  lexer_ = &lexer;
}

std::unique_ptr<INode> iCalendarParser::Parse() {
  return ParseStream();
}

std::unique_ptr<INode> iCalendarParser::ParseStream() {
  std::vector<std::unique_ptr<INode>> components;

  while (lexer_->Peek().tag != Tag::kEof) {
    components.push_back(ParseComponent());
  }

  return std::make_unique<StreamNode>(std::move(components));
}

std::unique_ptr<INode> iCalendarParser::ParseComponent() {
  std::string name = "";
  std::vector<std::unique_ptr<INode>> properties;
  std::vector<std::unique_ptr<INode>> components;

  if (lexer_->Peek() != kBegin) {
    return nullptr;
  }
  lexer_->Get();

  if (lexer_->Peek() != kColon) {
    return nullptr;
  }
  lexer_->Get();

  if (lexer_->Peek().tag != Tag::kIdentifier
      || !IsName(lexer_->Peek().image)) {
    return nullptr;
  }
  name = lexer_->Get().image;

  if (lexer_->Peek() != kCarriageReturn) {
    return nullptr;
  }
  lexer_->Get();

  if (lexer_->Peek() != kLineFeed) {
    return nullptr;
  }
  lexer_->Get();

  while (lexer_->Peek() != kBegin && lexer_->Peek() != kEnd) {
    properties.push_back(ParseProperty());
  }

  while (lexer_->Peek() != kEnd) {
    components.push_back(ParseComponent());
  }

  if (lexer_->Peek() != kEnd) {
    return nullptr;
  }
  lexer_->Get();

  if (lexer_->Peek() != kColon) {
    return nullptr;
  }
  lexer_->Get();

  if (lexer_->Peek().tag != Tag::kIdentifier
      || lexer_->Peek().image != name) {
    return nullptr;
  }
  lexer_->Get();

  if (lexer_->Peek() != kCarriageReturn) {
    return nullptr;
  }
  lexer_->Get();

  if (lexer_->Peek() != kLineFeed) {
    return nullptr;
  }
  lexer_->Get();
  
  return std::make_unique<ComponentNode>(std::move(name),
                                         std::move(properties),
                                         std::move(components));
}

std::unique_ptr<INode> iCalendarParser::ParseProperty() {
  // ...
}

bool iCalendarParser::IsName(const std::string& name) const {
  for (auto ch : name) {
    if (!('a' <= ch && ch <= 'z') && !('A' <= ch && ch <= 'z')
        && ch != '-') {
      return false;
    }
  }
  return true;
}
