#pragma once

#include "mainModel.hpp"


struct Ret_Prof {
  int prof_id;
  std::string name;
  int node_id;
};

class ProfileManager {
public:
  int add(Ret_Prof&);
  void remove(const int id);
  Ret_Prof get(const int id);


private:
  int id;
  dbo::Session &session_;
};