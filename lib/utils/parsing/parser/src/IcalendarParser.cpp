#include "IcalendarParser.hpp"

#include "IcalendarLexer.hpp"

namespace parser {
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

StreamUptr IcalendarParser::Parse() {
  return ParseStream();
}

void IcalendarParser::set_lexer(lexer::ILexer &lexer) {
  lexer_ = &lexer;
}

// stream = *component
StreamUptr IcalendarParser::ParseStream() {
  std::vector<ComponentUptr> components;

  // *component
  while (lexer_->Peek().tag != lexer::Tag::kEof) {
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
ComponentUptr IcalendarParser::ParseComponent() {
  std::string name = "";
  std::vector<PropertyUptr> properties;
  std::vector<ComponentUptr> components;

  // "BEGIN"
  if (lexer_->Peek() != lexer::kBegin) {
    return nullptr;
  }
  lexer_->Get();

  // ":"
  if (lexer_->Peek() != lexer::kColon) {
    return nullptr;
  }
  lexer_->Get();

  // name
  if (lexer_->Peek().tag != lexer::Tag::kIdentifier
      || !IsName(lexer_->Peek().image)) {
    return nullptr;
  }
  name = lexer_->Get().image;

  // "\r"
  if (lexer_->Peek() != lexer::kCarriageReturn) {
    return nullptr;
  }
  lexer_->Get();

  // "\n"
  if (lexer_->Peek() != lexer::kLineFeed) {
    return nullptr;
  }
  lexer_->Get();

  // *property
  while (lexer_->Peek() != lexer::kBegin
      && lexer_->Peek() != lexer::kEnd) {
    PropertyUptr property = ParseProperty();
    if (property) {
      properties.push_back(std::move(property));
    } else {
      return nullptr;
    }
  }

  // *component
  while (lexer_->Peek() != lexer::kEnd) {
    ComponentUptr component = ParseComponent();
    if (component) {
      components.push_back(std::move(component));
    } else {
      return nullptr;
    }
  }

  // "END"
  if (lexer_->Peek() != lexer::kEnd) {
    return nullptr;
  }
  lexer_->Get();

  // ":"
  if (lexer_->Peek() != lexer::kColon) {
    return nullptr;
  }
  lexer_->Get();

  // name
  // должно иметь то же значение, что и переменная name
  if (lexer_->Peek().tag != lexer::Tag::kIdentifier
      || lexer_->Peek().image != name) {
    return nullptr;
  }
  lexer_->Get();

  // "\r"
  if (lexer_->Peek() != lexer::kCarriageReturn) {
    return nullptr;
  }
  lexer_->Get();

  // "\n"
  if (lexer_->Peek() != lexer::kLineFeed) {
    return nullptr;
  }
  lexer_->Get();
  
  return std::make_unique<ComponentNode>(std::move(name),
                                         std::move(properties),
                                         std::move(components));
}

// property = name *parameter ":" value "\r" "\n"
PropertyUptr IcalendarParser::ParseProperty() {
  std::string name = "";
  std::vector<ParameterUptr> parameters;
  IValueUptr value = nullptr;

  // name
  if (lexer_->Peek().tag != lexer::Tag::kIdentifier
      || !IsName(lexer_->Peek().image)) {
    return nullptr;
  }
  name = lexer_->Get().image;

  // *parameter
  while (lexer_->Peek() != lexer::kColon) {
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
  if (lexer_->Peek() != lexer::kCarriageReturn) {
    return nullptr;
  }
  lexer_->Get();

  // "\n"
  if (lexer_->Peek() != lexer::kLineFeed) {
    return nullptr;
  }
  lexer_->Get();

  return std::make_unique<PropertyNode>(std::move(name),
                                        std::move(parameters),
                                        std::move(value));
}

// parameter = ";" pair-value
ParameterUptr IcalendarParser::ParseParameter() {
  PairValueUptr pair_value = nullptr;

  // ";"
  if (lexer_->Peek() != lexer::kSemicolon) {
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
IValueUptr IcalendarParser::ParseValue() {
  if (lexer_->Peek(1) != lexer::kEqual) {
    // text
    if (lexer_->Peek().tag != lexer::Tag::kIdentifier) {
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
    
    while (lexer_->Peek() == lexer::kSemicolon) {
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
PairValueUptr IcalendarParser::ParsePairValue() {
  std::string name = "";
  std::string text = "";

  // name
  if (lexer_->Peek().tag != lexer::Tag::kIdentifier
      || !(IsName(lexer_->Peek().image))) {
    return nullptr;
  }
  name = lexer_->Get().image;

  // "="
  if (lexer_->Peek() != lexer::kEqual) {
    return nullptr;
  }
  lexer_->Get();

  // text
  if (lexer_->Peek().tag != lexer::Tag::kIdentifier) {
    return nullptr;
  }
  text = lexer_->Get().image;

  return std::make_unique<PairValue>(std::move(name),
                                     std::move(text));
}

bool IcalendarParser::IsName(const std::string& name) const {
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
} // namespace parser
