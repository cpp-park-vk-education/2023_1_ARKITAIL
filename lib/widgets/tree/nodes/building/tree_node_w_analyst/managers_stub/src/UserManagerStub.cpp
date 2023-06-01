#include "UserManagerStub.hpp"

UserManagerStub::UserManagerStub(std::vector<User> users) :
    users_(users) {}

const User& UserManagerStub::get() {
    return users_[0];
}

const User& UserManagerStub::get(size_t user_id) {
    return users_[user_id];
}
