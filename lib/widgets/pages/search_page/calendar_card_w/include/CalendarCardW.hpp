#pragma once

#include <Wt/WAnchor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>
#include <vector>

#include "TagW.hpp"
#include "Calendar.hpp"
#include "User.hpp"

class CalendarCardW : public Wt::WContainerWidget {
public:
	CalendarCardW();
	CalendarCardW(
		const User& user,
		const Calendar& calendar,
		const std::vector<Tag>& tags);

private:
	Wt::WText* title_;
	Wt::WText* descriptions_;
	std::vector<TagW*> tags_;
	Wt::WAnchor* username_;
	Wt::WImage* avatar_;

};

