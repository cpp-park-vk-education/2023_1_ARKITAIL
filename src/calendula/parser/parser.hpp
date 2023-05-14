#pragma once

#include <memory>
#include <string>
#include <vector>

#include "lexer.hpp"

class INode;
class StreamNode;
class ComponentNode;
class PropertyNode;
class ParameterNode;

class IValue;
class TextValue;
class PairValue;
class CompositeValue;

class IParser;
class iCalendarParser;

class INode {
 public:
  virtual ~INode() = default;
};

class StreamNode : public INode {
 public:
  using Components = std::vector<std::unique_ptr<ComponentNode>>;

  StreamNode(Components&& components)
    : components_(std::move(components)) {
  }

  const Components& components() const {
    return components_;
  }
 private:
   Components components_;
};

class ComponentNode : public INode {
 public:
  using Components = std::vector<std::unique_ptr<ComponentNode>>;
  using Properties = std::vector<std::unique_ptr<PropertyNode>>;

  ComponentNode(std::string&& name,
                Properties&& properties,
                Components&& components)
    : name_(std::move(name)),
      properties_(std::move(properties)),
      components_(std::move(components)) {
  }

  const std::string& name() const {
    return name_;
  }

  const Properties& properties() const {
    return properties_;
  }

  const Components& components() const {
    return components_;
  }
 private:
  std::string name_;
  Properties properties_;
  Components components_;
};

class PropertyNode : public INode {
 public:
  using Parameters = std::vector<std::unique_ptr<ParameterNode>>;

  PropertyNode(std::string&& name,
               Parameters&& parameters,
               std::unique_ptr<IValue>&& value)
    : name_(std::move(name)),
      parameters_(std::move(parameters)),
      value_(std::move(value)) {
  }

  const std::string& name() const {
    return name_;
  }

  const Parameters& parameters() const {
    return parameters_;
  }

  const std::unique_ptr<IValue>& value() const {
    return value_;
  }
 private:
  std::string name_;
  Parameters parameters_;
  std::unique_ptr<IValue> value_;
};

class ParameterNode : public INode {
 public:
  ParameterNode(std::unique_ptr<PairValue>&& pair_value)
    : pair_value_(std::move(pair_value)) {
  }

  const std::unique_ptr<PairValue>& pair_value() const {
    return pair_value_;
  }
 private:
  std::unique_ptr<PairValue> pair_value_;
};

class IValue {
 public:
  virtual ~IValue() = default;
};

class TextValue : public IValue {
 public:
  TextValue(std::string&& text)
    : text_(std::move(text)) {
  }

  const std::string& text() const {
    return text_;
  }
 private:
  std::string text_;
};

class PairValue : public TextValue {
 public:
  PairValue(std::string&& name,
            std::string&& text)
    : TextValue(std::move(text)),
      name_(std::move(name)) {
  }

  const std::string& name() const {
    return name_;
  }
 private:
  std::string name_;
};

class CompositeValue : public IValue {
 public:
  using Values = std::vector<std::unique_ptr<IValue>>;

  CompositeValue(Values&& values)
    : values_(std::move(values)) {
  }

  const Values& values() const {
    return values_;
  }
 private:
  Values values_;
};

class IParser {
 public:
  // возвращает корень абстрактного синтаксического дерева
  virtual std::unique_ptr<INode> Parse() = 0;
  
  virtual ~IParser() = default;
};

class iCalendarParser : public IParser {
 public:
  std::unique_ptr<INode> Parse() override;

  void set_lexer(ILexer& lexer);
 private:
  std::unique_ptr<StreamNode> ParseStream();
  std::unique_ptr<ComponentNode> ParseComponent();
  std::unique_ptr<PropertyNode> ParseProperty();
  std::unique_ptr<ParameterNode> ParseParameter();

  std::unique_ptr<IValue> ParseValue();
  std::unique_ptr<PairValue> ParsePairValue();

  bool IsName(const std::string& name) const;

  ILexer* lexer_;
};
