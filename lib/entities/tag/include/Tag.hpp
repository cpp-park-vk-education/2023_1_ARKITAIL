#pragma once

#include <memory>
#include <string>

class Tag;
using TagSptr = std::shared_ptr<Tag>;

class Tag {
public:
  Tag() = default;
  Tag(int id, std::string name);

  bool operator==(const Tag& a) const;
  
  int id;
  std::string name;

};

