#include "OtherUserW.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WText.h>

#include <memory>

OtherUserW::OtherUserW(const User& user) :
    UserWBase(user),
    nickname_(nickname_block_->addWidget(std::make_unique<UserAnchorW>("", user))) {}
