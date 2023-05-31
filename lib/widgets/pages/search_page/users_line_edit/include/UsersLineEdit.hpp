#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WSignal.h>

#include "ItemsContainerW.hpp"
#include "User.hpp"

class UsersLineEdit : public Wt::WContainerWidget {
public:
	UsersLineEdit();
	void parseItem(const std::string& user_name);

private:
	Wt::WLineEdit* line_edit_;
	ItemsContainerW<User> users_;

	Wt::Signal<User> added_;
	Wt::Signal<User> removed_;

};

