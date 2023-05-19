#include "User.hpp"

User::User() :
	id(),
	root_id(),
	login(),
	email(),
	nickname(),
	description() {}

User::User(size_t id, size_t root_id, std::string login, std::string email, std::string nickname, std::string description) :
	id(id),
	root_id(root_id),
	login(login),
	email(email),
	nickname(nickname),
	description(description) {}


