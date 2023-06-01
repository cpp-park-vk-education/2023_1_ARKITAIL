#include "UsersLineEdit.hpp"
#include "RemovableItemW.hpp"
#include <memory>

UsersLineEdit::UsersLineEdit() :
	Wt::WContainerWidget() {}

void UsersLineEdit::parseItem(const std::string& user_name) {
	User user = User(0, 0, "login", "email", user_name, "description");
	auto item = std::make_unique<RemovableItemW<User>>(user);

	item->clicked()->connect([&](){
		removed_.emit(user);
	});

	users_.addItem(std::move(item));

	added_.emit(user);
}

