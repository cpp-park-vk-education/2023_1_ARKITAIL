#pragma once

#include "mainModel.hpp"


struct RetProf {
  int prof_id;
  std::string name;
  int node_id;
};

class ProfileManager {
public:
  ProfileManager(dbo::Session &session) : session_(session) {}


  int Add(RetProf&);
  void Remove(int id);
  RetProf Get(int id);


private:
  int id_;
  dbo::Session &session_;
};