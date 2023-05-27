#pragma once

#include <memory>
#include <string>

class Tag;
using TagSptr = std::shared_ptr<Tag>;

class Tag {
public:
  Tag() = default;
  Tag(int id, std::string name);
  
  int id;
  std::string name;

};

