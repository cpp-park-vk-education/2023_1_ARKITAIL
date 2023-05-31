#include "CalendarCardContainerW.hpp"
#include "Calendar.hpp"
#include "CalendarCardW.hpp"
#include <vector>

CalendarCardContainerW::CalendarCardContainerW() :
	status_(),
	calendar_cards_() {}

void CalendarCardContainerW::init(const std::vector<Calendar>& content) {
	for (auto card : content)
		calendar_cards_.push_back(addWidget(std::make_unique<CalendarCardW>(User(), card, std::vector<Tag>())));
}

