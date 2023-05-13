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
class StringValue;
class PairValue;
class CompositeValue;

class IParser;
class iCalendarParser;

// TODO: добавить геттеры, сеттеры

class INode {
 public:
  virtual ~INode() = default;
};

class StreamNode : public INode {
 public:
  StreamNode(std::vector<std::unique_ptr<INode>>&& components)
    : components_(std::move(components)) {
  }
 private:
   std::vector<std::unique_ptr<INode>> components_;
};

class ComponentNode : public INode {
 public:
  ComponentNode(std::string&& name,
                std::vector<std::unique_ptr<INode>>&& properties,
                std::vector<std::unique_ptr<INode>>&& components)
    : name_(std::move(name)),
      properties_(std::move(properties)),
      components_(std::move(components)) {
  }
 private:
  std::string name_;
  std::vector<std::unique_ptr<INode>> properties_;
  std::vector<std::unique_ptr<INode>> components_;
};

class PropertyNode : public INode {
 public:
  PropertyNode(std::string&& name,
               std::vector<std::unique_ptr<INode>>&& parameters,
               std::vector<std::unique_ptr<IValue>>&& value)
    : name_(std::move(name)),
      parameters_(std::move(parameters)),
      value_(std::move(value)) {
  }
 private:
  std::string name_;
  std::vector<std::unique_ptr<INode>> parameters_;
  std::vector<std::unique_ptr<IValue>> value_;
};

class ParameterNode : public INode {
 public:
  ParameterNode(std::unique_ptr<IValue>&& value)
    : value_(std::move(value)) {
  }
 private:
  std::unique_ptr<IValue> value_;
};

class IValue {
 public:
  virtual ~IValue() = default;
};

class StringValue : public IValue {
 public:
  StringValue(std::string&& value)
    : value_(std::move(value)) {
  }
 private:
  std::string value_;
};

class PairValue : public IValue {
 public:
  PairValue(std::string&& key,
            std::string&& value)
    : key_(std::move(key)),
      value_(std::move(value)) {
  }
 private:
  std::string key_;
  std::string value_;
};

class CompositeValue : public IValue {
  CompositeValue(std::vector<std::unique_ptr<IValue>>&& values)
    : values_(std::move(values)) {
  }
 private:
  std::vector<std::unique_ptr<IValue>> values_;
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
  std::unique_ptr<INode> ParseStream();
  std::unique_ptr<INode> ParseComponent();
  std::unique_ptr<INode> ParseProperty();
  std::unique_ptr<INode> ParseParameter();
  bool IsName(const std::string& name) const;

  ILexer* lexer_;
};
