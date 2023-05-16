#pragma once

#include "Main_model.hpp"

struct Ret_Tag {
  std::string name;
};

class tag_manager {
public:
  tag_manager(dbo::Session &session) : session_(session) {}

  int addTag(Ret_Tag &);
  void remoteTag(const int id);
  Ret_Tag getTag(const int id);

private:
  int id;
  dbo::Session &session_;
};