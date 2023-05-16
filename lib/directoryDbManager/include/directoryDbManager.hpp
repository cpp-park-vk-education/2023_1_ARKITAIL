#pragma once

#include "mainModel.hpp"

struct Ret_Dir {
  std::string name;
  std::string description;
  int node_id;
};

class DirectoryManager {
public:
  int add(Ret_Dir &);
  void remove(const int id);
  void update(Ret_Dir &);
  Ret_Dir get(const int id);

private:
  int id;
  dbo::Session &session_;
};