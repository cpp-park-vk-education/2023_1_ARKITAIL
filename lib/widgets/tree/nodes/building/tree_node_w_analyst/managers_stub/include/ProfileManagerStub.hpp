#pragma once

#include <memory>

#include "IProfileManager.hpp"
#include "Profile.hpp"

class ProfileManagerStub : public IProfileManager {
  public:
    explicit ProfileManagerStub(std::vector<Profile> profiles);

    ProfileSptr get(int profile_id) override;
    int add(ProfileSptr profile, int directory_id) override {}
    void update(ProfileSptr profile) override {}
    void remove(int profile_id) override {}

  private:
    std::vector<Profile> profiles_;
};
