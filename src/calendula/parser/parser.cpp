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

property       = name *parameter ":" value "\r" "\n"
   
               ; TODO: случай с 
               ; несколькими значениями
parameter      = ";" pair-value

value          = text / ( pair-value *( ";" pair-value ) )

pair-value     = name "=" text

name           = *( ALPHA / DIGIT / "-" )

text           = любые символы, за исключением ";", "=" и "\r"
*/

std::unique_ptr<INode> iCalendarParser::Parse() {
  return ParseStream();
}

void iCalendarParser::set_lexer(ILexer &lexer) {
  lexer_ = &lexer;
}

// stream = *component
std::unique_ptr<StreamNode> iCalendarParser::ParseStream() {
  std::vector<std::unique_ptr<ComponentNode>> components;

  // *component
  while (lexer_->Peek().tag != Tag::kEof) {
    components.push_back(ParseComponent());
  }

  return std::make_unique<StreamNode>(std::move(components));
}

// component = "BEGIN" ":" name "\r" "\n"
//             *property
//             *component
//             "END" ":" name "\r" "\n"
std::unique_ptr<ComponentNode> iCalendarParser::ParseComponent() {
  std::string name = "";
  std::vector<std::unique_ptr<PropertyNode>> properties;
  std::vector<std::unique_ptr<ComponentNode>> components;

  // "BEGIN"
  if (lexer_->Peek() != kBegin) {
    return nullptr;
  }
  lexer_->Get();

  // ":"
  if (lexer_->Peek() != kColon) {
    return nullptr;
  }
  lexer_->Get();

  // name
  if (lexer_->Peek().tag != Tag::kIdentifier
      || !IsName(lexer_->Peek().image)) {
    return nullptr;
  }
  name = lexer_->Get().image;

  // "\r"
  if (lexer_->Peek() != kCarriageReturn) {
    return nullptr;
  }
  lexer_->Get();

  // "\n"
  if (lexer_->Peek() != kLineFeed) {
    return nullptr;
  }
  lexer_->Get();

  // *property
  while (lexer_->Peek() != kBegin
      && lexer_->Peek() != kEnd) {
    properties.push_back(ParseProperty());
  }

  // *component
  while (lexer_->Peek() != kEnd) {
    components.push_back(ParseComponent());
  }

  // "END"
  if (lexer_->Peek() != kEnd) {
    return nullptr;
  }
  lexer_->Get();

  // ":"
  if (lexer_->Peek() != kColon) {
    return nullptr;
  }
  lexer_->Get();

  // name
  // должно иметь то же значение, что и переменная name
  if (lexer_->Peek().tag != Tag::kIdentifier
      || lexer_->Peek().image != name) {
    return nullptr;
  }
  lexer_->Get();

  // "\r"
  if (lexer_->Peek() != kCarriageReturn) {
    return nullptr;
  }
  lexer_->Get();

  // "\n"
  if (lexer_->Peek() != kLineFeed) {
    return nullptr;
  }
  lexer_->Get();
  
  return std::make_unique<ComponentNode>(std::move(name),
                                         std::move(properties),
                                         std::move(components));
}

// property = name *parameter ":" value "\r" "\n"
std::unique_ptr<PropertyNode> iCalendarParser::ParseProperty() {
  std::string name = "";
  std::vector<std::unique_ptr<ParameterNode>> parameters;
  std::unique_ptr<IValue> value = nullptr;

  // name
  if (lexer_->Peek().tag != Tag::kIdentifier
      || !IsName(lexer_->Peek().image)) {
    return nullptr;
  }
  name = lexer_->Get().image;

  // *parameter
  while (lexer_->Peek() != kColon) {
    parameters.push_back(ParseParameter());
  }

  // ":"
  lexer_->Get();

  // value
  value = ParseValue();

  // "\r"
  if (lexer_->Peek() != kCarriageReturn) {
    return nullptr;
  }
  lexer_->Get();

  // "\n"
  if (lexer_->Peek() != kLineFeed) {
    return nullptr;
  }
  lexer_->Get();

  return std::make_unique<PropertyNode>(std::move(name),
                                        std::move(parameters),
                                        std::move(value));
}

// parameter = ";" pair-value
std::unique_ptr<ParameterNode> iCalendarParser::ParseParameter() {
  std::unique_ptr<PairValue> pair_value = nullptr;

  // ";"
  if (lexer_->Peek() != kSemicolon) {
    return nullptr;
  }
  lexer_->Get();

  // pair-value
  pair_value = ParsePairValue();

  return std::make_unique<ParameterNode>(std::move(pair_value));
}

// value = text / ( pair-value *( ";" pair-value ) )
std::unique_ptr<IValue> iCalendarParser::ParseValue() {
  if (lexer_->Peek(1) != kEqual) {
    // text
    if (lexer_->Peek().tag != Tag::kIdentifier) {
      return nullptr;
    }

    return std::make_unique<TextValue>(std::move(lexer_->Get().image));
  } else {
    std::vector<std::unique_ptr<IValue>> values;

    // ( pair-value *( ";" pair-value ) )
    do {
      values.push_back(ParsePairValue());
    } while (lexer_->Peek() == kSemicolon);
    
    return std::make_unique<CompositeValue>(std::move(values));
  }
}

// pair-value = name "=" text
std::unique_ptr<PairValue> iCalendarParser::ParsePairValue() {
  std::string name = "";
  std::string text = "";

  // name
  if (lexer_->Peek().tag != Tag::kIdentifier
      || !(IsName(lexer_->Peek().image))) {
    return nullptr;
  }
  name = lexer_->Get().image;

  // "="
  if (lexer_->Peek() != kColon) {
    return nullptr;
  }
  lexer_->Get();

  // value
  if (lexer_->Peek().tag != Tag::kIdentifier) {
    return nullptr;
  }
  text = lexer_->Get().image;

  return std::make_unique<PairValue>(std::move(name),
                                     std::move(text));
}

bool iCalendarParser::IsName(const std::string& name) const {
  for (auto ch : name) {
    if (!('a' <= ch && ch <= 'z')
        && !('A' <= ch && ch <= 'z')
        && !('0' <= ch && ch <= '9')
        && ch != '-') {
      return false;
    }
  }
  return true;
}
