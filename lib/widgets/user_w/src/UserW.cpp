#include "UserW.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WText.h>

#include <memory>

UserW::UserW(const User& user) :
    UserWBase(user),
    nickname_(nickname_block_->addWidget(std::make_unique<Wt::WText>(user.nickname))) {}

void UserW::setNickname(std::string nickname) {
    nickname_->setText(nickname);
}

void UserW::setAvatar(std::string avatar_link) {
    avatar_->setImageLink(Wt::WLink(avatar_link));
}

void UserW::setDescription(std::string description) {
    description_->setText(description);
}
