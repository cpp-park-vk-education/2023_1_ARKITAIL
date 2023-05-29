#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <vector>

class CalendarCardW : public Wt::WContainerWidget {
public:
	CalendarCardW();

private:
	Wt::WText* title_;
	Wt::WText* descriptions_;

};

