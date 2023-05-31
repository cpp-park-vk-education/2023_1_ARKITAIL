#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <memory>

#include "SearchPage.hpp"
#include "TagsLineEdit.hpp"
#include "UsersLineEdit.hpp"

SearchP::SearchP() :
	users_(addWidget(std::make_unique<UsersLineEdit>())),
	tags_(addWidget(std::make_unique<TagsLineEdit>())),
	hint_(addWidget(std::make_unique<Wt::WText>())),
	found_(addWidget(std::make_unique<CalendarCardContainerW>())),
	searcher_() {

	users_->parseItem("ХУЙ");
	users_->parseItem("ХУЙ");
	users_->parseItem("ХУЙ");
	users_->parseItem("ХУЙ");
}

void SearchP::search() {}

