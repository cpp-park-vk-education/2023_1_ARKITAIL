#include "UsersLineEdit.hpp"
#include "ItemsContainerW.hpp"
#include "RemovableItemW.hpp"
#include "SessionScopeMap.hpp"
#include "Managers.hpp"
#include <Wt/WLineEdit.h>
#include <memory>

UsersLineEdit::UsersLineEdit() :
	Wt::WContainerWidget(),
	line_edit_(addWidget(std::make_unique<Wt::WLineEdit>())), 
	users_(addWidget(std::make_unique<ItemsContainerW<User>>())),
	added_(),
	removed_() {

	auto cm = SessionScopeMap::instance().get()->connections_mediator();
}

void UsersLineEdit::parseItem(const std::string& user_name) {
	User user = User(0, 0, "login", "email", user_name, "description");
	auto item = std::make_unique<RemovableItemW<User>>(user_name, user);

	item->item_clicked()->connect([this, user](){
		this->removed_.emit(user);
	});

	users_->addItem(std::move(item));

	added_.emit(user);
}

