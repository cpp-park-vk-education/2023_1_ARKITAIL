#pragma once

#include "mainModel.hpp"

struct RetDir {
  int dir_id;
  std::string name;
  std::string description;
  int node_id;
};

class DirectoryManager {
public:
  int Add(RetDir &);
  void Remove(int id);
  void Update(RetDir &);
  RetDir Get(int id);

private:
  int id_;
  dbo::Session &session_;
};