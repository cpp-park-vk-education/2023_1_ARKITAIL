#pragma once

#include "mainModel.hpp"

struct Ret_Tag {
  std::string name;
};

class tag_manager {
public:
  tag_manager(dbo::Session &session) : session_(session) {}

  int add(Ret_Tag &);
  void remote(const int id);
  Ret_Tag get(const int id);

private:
  int id;
  dbo::Session &session_;
};