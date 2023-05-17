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

StreamUptr iCalendarParser::Parse() {
  return ParseStream();
}

void iCalendarParser::set_lexer(ILexer &lexer) {
  lexer_ = &lexer;
}

// stream = *component
StreamUptr iCalendarParser::ParseStream() {
  std::vector<ComponentUptr> components;

  // *component
  while (lexer_->Peek().tag != Tag::kEof) {
    ComponentUptr component = ParseComponent();
    if (component) {
      components.push_back(std::move(component));
    } else {
      return nullptr;
    }
  }

  return std::make_unique<StreamNode>(std::move(components));
}

// component = "BEGIN" ":" name "\r" "\n"
//             *property
//             *component
//             "END" ":" name "\r" "\n"
ComponentUptr iCalendarParser::ParseComponent() {
  std::string name = "";
  std::vector<PropertyUptr> properties;
  std::vector<ComponentUptr> components;

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
    PropertyUptr property = ParseProperty();
    if (property) {
      properties.push_back(std::move(property));
    } else {
      return nullptr;
    }
  }

  // *component
  while (lexer_->Peek() != kEnd) {
    ComponentUptr component = ParseComponent();
    if (component) {
      components.push_back(std::move(component));
    } else {
      return nullptr;
    }
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
PropertyUptr iCalendarParser::ParseProperty() {
  std::string name = "";
  std::vector<ParameterUptr> parameters;
  IValueUptr value = nullptr;

  // name
  if (lexer_->Peek().tag != Tag::kIdentifier
      || !IsName(lexer_->Peek().image)) {
    return nullptr;
  }
  name = lexer_->Get().image;

  // *parameter
  while (lexer_->Peek() != kColon) {
    ParameterUptr parameter = ParseParameter();
    if (parameter) {
      parameters.push_back(std::move(parameter));
    } else {
      return nullptr;
    }
  }

  // ":"
  lexer_->Get();

  // value
  value = ParseValue();
  if (!value) {
    return nullptr;
  }

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
ParameterUptr iCalendarParser::ParseParameter() {
  PairValueUptr pair_value = nullptr;

  // ";"
  if (lexer_->Peek() != kSemicolon) {
    return nullptr;
  }
  lexer_->Get();

  // pair-value
  pair_value = ParsePairValue();
  if (!pair_value) {
    return nullptr;
  }

  return std::make_unique<ParameterNode>(std::move(pair_value));
}

// value = text / ( pair-value *( ";" pair-value ) )
IValueUptr iCalendarParser::ParseValue() {
  if (lexer_->Peek(1) != kEqual) {
    // text
    if (lexer_->Peek().tag != Tag::kIdentifier) {
      return nullptr;
    }

    return std::make_unique<TextValue>(std::move(lexer_->Get().image));
  } else {
    std::vector<IValueUptr> values;

    // pair-value
    PairValueUptr pair_value = ParsePairValue();
    if (pair_value) {
      values.push_back(std::move(pair_value));
    } else {
      return nullptr;
    }
    
    while (lexer_->Peek() == kSemicolon) {
      // ";"
      lexer_->Get();

      // pair-value
      PairValueUptr pair_value = ParsePairValue();
      if (pair_value) {
        values.push_back(std::move(pair_value));
      } else {
        return nullptr;
      }
    }
    
    return std::make_unique<CompositeValue>(std::move(values));
  }
}

// pair-value = name "=" text
PairValueUptr iCalendarParser::ParsePairValue() {
  std::string name = "";
  std::string text = "";

  // name
  if (lexer_->Peek().tag != Tag::kIdentifier
      || !(IsName(lexer_->Peek().image))) {
    return nullptr;
  }
  name = lexer_->Get().image;

  // "="
  if (lexer_->Peek() != kEqual) {
    return nullptr;
  }
  lexer_->Get();

  // text
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
