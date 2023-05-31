#include "OtherUserP.hpp"

#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"

OtherUserP::OtherUserP() :
    test_(addWidget(std::make_unique<Wt::WText>(""))) {

    auto cm = SessionScopeMap::instance().get()->connections_mediator();
    cm->swap_to_profile_page.add_receiver(this, &OtherUserP::init);
}

void OtherUserP::init(const User& user) {
    test_->setText("Переход на страницу " + user.nickname);
}
