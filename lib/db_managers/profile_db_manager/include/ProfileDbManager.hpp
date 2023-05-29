#pragma once

#include <Wt/Dbo/Session.h>

#include "IProfileDbManager.hpp"
#include "Profile.hpp"

class ProfileDbManager : public IProfileDbManager {
public:
  explicit ProfileDbManager(Wt::Dbo::Session &session) : session_(session) {}

  int add(ProfileSptr profile) override;
  void remove(int profile_id) override;
  void update(ProfileSptr profile) override;
  ProfileSptr get(int profile_id) override;

private:
  int id_;
  Wt::Dbo::Session &session_;
};
