#pragma once

#include "mainModel.hpp"


struct Ret_Comm {
  std::string name;
  std::string text;
  int event_id;
};

class CommentManager {
public:
  int add(Ret_Comm&);
  void remove(const int id);
  Ret_Comm get(const int id);


private:
  int id;
  dbo::Session &session_;
};