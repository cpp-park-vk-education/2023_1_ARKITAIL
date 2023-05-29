#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <vector>

#include "CalendarCardW.hpp"

class CalendarCardContainerW : public Wt::WContainerWidget {
public:
	CalendarCardContainerW();

private:
	Wt::WText* text_;
	std::vector<CalendarCardW*> calendar_cards_; 

};
