#include "CalendarCardContainerW.hpp"

#include <vector>

#include "Calendar.hpp"
#include "CalendarCardW.hpp"
#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"

CalendarCardContainerW::CalendarCardContainerW() :
    status_(),
    calendar_cards_() {
    addStyleClass("container-md mx-auto");
}

void CalendarCardContainerW::init(const std::vector<CalendarSptr>& content) {
    for (auto card : content) {
        User user =
            *SessionScopeMap::instance().get()->managers()->user_manager()->get(card->owner_id);
        calendar_cards_.push_back(addWidget(std::make_unique<CalendarCardW>(
            user, card, std::vector<Tag>{Tag(0, "tag1"), Tag(0, "tag2"), Tag(0, "tag3")})));
    }
}
