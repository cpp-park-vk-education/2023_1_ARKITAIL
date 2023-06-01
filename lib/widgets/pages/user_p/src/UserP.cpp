#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"
#include "UserP.hpp"

UserP::UserP() :
    test_(addWidget(std::make_unique<Wt::WText>(""))) {}

void UserP::init(const User& user) {
    test_->setText("Мой профиль");
}
