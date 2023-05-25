#pragma once

#include "mainModel.hpp"
#include "IProfileDbManager.hpp"


class ProfileDbManager: public IProfileDbManager {
public:
  ProfileDbManager(dbo::Session &session) : session_(session) {}

  int add(const Profile &);
  void remove(int profile_id);
  void update( const Profile&);
  const Profile& get(int profile_id);

private:
  int id_;
  dbo::Session &session_;
};