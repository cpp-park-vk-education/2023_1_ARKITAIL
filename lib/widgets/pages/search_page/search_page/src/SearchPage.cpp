#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <memory>

#include "SearchPage.hpp"

SearchP::SearchP() :
	input_users_(addWidget(std::make_unique<Wt::WLineEdit>())),
	input_tags_(addWidget(std::make_unique<Wt::WLineEdit>())),
	find_button_(addWidget(std::make_unique<Wt::WPushButton>())),
	hint_(addWidget(std::make_unique<Wt::WText>())),
	found_(addWidget(std::make_unique<CalendarCardContainerW>())),
	searcher_() {

}

void SearchP::search() {}

