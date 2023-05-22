#pragma once

#include "mainModel.hpp"


struct RetComm {
  int com_id;
  std::string name;
  std::string text;
  int event_id;
};

class CommentManager {
public:
  int Add(RetComm&);
  void Remove(int id);
  RetComm Get(int id);


private:
  int id_;
  dbo::Session &session_;
};