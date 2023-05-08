#pragma once

class ICharacterReader {
 public:
  virtual char Peek() = 0;
  virtual char Get() = 0;
  virtual bool IsEOF() const = 0;
   
  virtual ~ICharacterReader() = default;
};
