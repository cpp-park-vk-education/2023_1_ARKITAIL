#pragma once

#include "IProfileDbManager.hpp"
#include "Profile.hpp"
#include "Session.hpp"

class ProfileDbManager : public IProfileDbManager {
public:
  ProfileDbManager() = delete;
  explicit ProfileDbManager(Session& session);

  int add(ProfileSptr profile) override;
  void remove(int profile_id) override;
  void update(ProfileSptr profile) override;
  ProfileSptr get(int profile_id) override;

private:
  Session& session_;

};

