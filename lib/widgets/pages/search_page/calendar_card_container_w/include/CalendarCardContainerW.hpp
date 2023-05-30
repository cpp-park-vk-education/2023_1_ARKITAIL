#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <vector>

#include "CalendarCardW.hpp"
#include "Calendar.hpp"

class CalendarCardContainerW : public Wt::WContainerWidget {
public:
	CalendarCardContainerW();
	void init(const std::vector<Calendar>& content);

private:
	Wt::WText* status_;
	std::vector<CalendarCardW*> calendar_cards_; 

};
