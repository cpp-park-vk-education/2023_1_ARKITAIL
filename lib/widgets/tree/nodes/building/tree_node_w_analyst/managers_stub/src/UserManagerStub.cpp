#include "UserManagerStub.hpp"

UserManagerStub::UserManagerStub(std::vector<User> users) :
    users_(users) {}

UserSptr UserManagerStub::get() {
    return std::make_shared<User>(users_[0]);
}

UserSptr UserManagerStub::get(int user_id) {
    return std::make_shared<User>(users_[user_id]);
}
