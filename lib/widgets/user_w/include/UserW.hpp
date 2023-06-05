#pragma once

#include "UserWBase.hpp"

class UserW : public UserWBase {
  public:
    UserW(const User& user);
    ~UserW() = default;

    void setNickname(std::string nickname);
    void setAvatar(std::string avatar_link);
    void setDescription(std::string description);

  private:
    Wt::WText* nickname_;
    
};
