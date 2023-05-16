#pragma once

#include "Main_model.hpp"

struct Ret_Dir {
  std::string name;
  std::string description;
  int node_id;
};

class directory_manager {
public:
  int addDirectory(Ret_Dir &);
  void removeDirectory(const int id);
  void updateDirectory(Ret_Dir &);
  Ret_Dir getDirectory(const int id);

private:
  int id;
  dbo::Session &session_;
};