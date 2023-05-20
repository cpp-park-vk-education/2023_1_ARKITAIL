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
class IcalendarParser;

using StreamUptr = std::unique_ptr<StreamNode>;
using ComponentUptr = std::unique_ptr<ComponentNode>;
using PropertyUptr = std::unique_ptr<PropertyNode>;
using ParameterUptr = std::unique_ptr<ParameterNode>;

using IValueUptr = std::unique_ptr<IValue>;
using PairValueUptr = std::unique_ptr<PairValue>;

class INode {
 public:
  virtual ~INode() = default;
};

class StreamNode : public INode {
 public:
  StreamNode(std::vector<ComponentUptr>&& components)
    : components_(std::move(components)) {
  }

  std::vector<ComponentUptr>& components() {
    return components_;
  }
 private:
   std::vector<ComponentUptr> components_;
};

class ComponentNode : public INode {
 public:
  ComponentNode(std::string&& name,
                std::vector<PropertyUptr>&& properties,
                std::vector<ComponentUptr>&& components)
    : name_(std::move(name)),
      properties_(std::move(properties)),
      components_(std::move(components)) {
  }

  std::string& name() {
    return name_;
  }

  std::vector<PropertyUptr>& properties() {
    return properties_;
  }

  std::vector<ComponentUptr>& components() {
    return components_;
  }
 private:
  std::string name_;
  std::vector<PropertyUptr> properties_;
  std::vector<ComponentUptr> components_;
};

class PropertyNode : public INode {
 public:
  PropertyNode(std::string&& name,
               std::vector<ParameterUptr>&& parameters,
               std::unique_ptr<IValue>&& value)
    : name_(std::move(name)),
      parameters_(std::move(parameters)),
      value_(std::move(value)) {
  }

  std::string& name() {
    return name_;
  }

  std::vector<ParameterUptr>& parameters() {
    return parameters_;
  }

  IValueUptr& value() {
    return value_;
  }
 private:
  std::string name_;
  std::vector<ParameterUptr> parameters_;
  IValueUptr value_;
};

class ParameterNode : public INode {
 public:
  ParameterNode(std::unique_ptr<PairValue>&& pair_value)
    : pair_value_(std::move(pair_value)) {
  }

  PairValueUptr& pair_value() {
    return pair_value_;
  }
 private:
  PairValueUptr pair_value_;
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

  std::string& text() {
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

  std::string& name() {
    return name_;
  }
 private:
  std::string name_;
};

class CompositeValue : public IValue {
 public:
  CompositeValue(std::vector<IValueUptr>&& values)
    : values_(std::move(values)) {
  }

  std::vector<IValueUptr>& values() {
    return values_;
  }
 private:
  std::vector<IValueUptr> values_;
};

class IParser {
 public:
  // возвращает корень абстрактного синтаксического дерева
  virtual std::unique_ptr<StreamNode> Parse() = 0;
  
  virtual ~IParser() = default;
};

class IcalendarParser : public IParser {
 public:
  std::unique_ptr<StreamNode> Parse() override;

  void set_lexer(ILexer& lexer);
 private:
  StreamUptr ParseStream();
  ComponentUptr ParseComponent();
  PropertyUptr ParseProperty();
  ParameterUptr ParseParameter();

  IValueUptr ParseValue();
  PairValueUptr ParsePairValue();

  bool IsName(const std::string& name) const;

  ILexer* lexer_;
};
