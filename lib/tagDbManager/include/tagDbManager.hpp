#pragma once

#include "mainModel.hpp"

struct RetTag {
  int tag_id;
  std::string name;
};

class TagManager {
public:
  TagManager(dbo::Session &session) : session_(session) {}

  int Add(RetTag &);
  void Remove(int id);
  RetTag Get(int id);

private:
  int id_;
  dbo::Session &session_;
};