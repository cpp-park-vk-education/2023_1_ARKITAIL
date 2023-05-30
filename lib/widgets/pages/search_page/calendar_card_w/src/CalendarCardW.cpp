#include <Wt/WText.h>
#include <memory>
#include <vector>

#include "CalendarCardW.hpp"
#include "User.hpp"

CalendarCardW::CalendarCardW() :
	title_(),
	descriptions_(),
	tags_(),
	username_(),
	avatar_() {}

CalendarCardW::CalendarCardW(const User& user, const Calendar& calendar, const std::vector<Tag>& tags) :
	title_(addWidget(std::make_unique<Wt::WText>(calendar.summary))),
	descriptions_(addWidget(std::make_unique<Wt::WText>(calendar.description))),
	tags_(),
	username_(),
	avatar_() {}

