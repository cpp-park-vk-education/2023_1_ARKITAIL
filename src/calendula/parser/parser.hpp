#pragma once

class IParser {
 public:
  virtual ~IParser() = default;
};

class iCalnedarParser : public IParser {
 public:
  // ...
};
