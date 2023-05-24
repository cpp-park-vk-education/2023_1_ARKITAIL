#pragma once

#include <memory>

#include "IParser.hpp"
#include "IcalendarLexer.hpp"

namespace parser {
class IcalendarParser : public IParser {
 public:
  std::unique_ptr<StreamNode> Parse() override;

  void set_lexer(lexer::ILexer& lexer);
 private:
  StreamUptr ParseStream();
  ComponentUptr ParseComponent();
  PropertyUptr ParseProperty();
  ParameterUptr ParseParameter();

  IValueUptr ParseValue();
  PairValueUptr ParsePairValue();

  bool IsName(const std::string& name) const;

  lexer::ILexer* lexer_;
};
} // namespace parser
