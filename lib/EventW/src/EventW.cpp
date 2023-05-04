#include "EventW.hpp"

#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include <Wt/WTime.h>

#include <memory>
#include <string>

void EventW::makeEventWidget(Wt::WTable *table, Wt::WDate begin_of_week) {
    int dayWeek = begin_.date().dayOfWeek();
    if (begin_.date().daysTo(end_.date())) {
        auto day = begin_.date() > begin_of_week ? begin_.date() : begin_of_week;
        table->elementAt(1, day.dayOfWeek())
            ->addWidget(std::move(makeEventPartWidget("w-100 text-nowrap rounded-start border-end-0")));
        day = day.addDays(1);
        for (; day < end_.date() && day < begin_of_week.addDays(7); day = day.addDays(1)) {
            table->elementAt(1, day.dayOfWeek())
                ->addWidget(std::move(makeEventPartWidget("w-100 text-nowrap border-start-0 border-end-0")));
        }
        if (day <= end_.date() && day < begin_of_week.addDays(7))
            table->elementAt(1, day.dayOfWeek())
                ->addWidget(std::move(makeEventPartWidget("w-100 text-nowrap rounded-end border-start-0")));

    } else {
        int h = begin_.time().hour();
        table->elementAt(h + 2, dayWeek % 8)
            ->addWidget(std::move(makeEventPartWidget("text-wrap rounded-top border-bottom-0")));
        h++;
        for (; h < end_.time().hour() - 1; h++) {
            table->elementAt(h + 2, dayWeek % 8)
                ->addWidget(std::move(makeEventPartWidget("text-wrap border-top-0 border-bottom-0")));
        }
        table->elementAt(h + 2, dayWeek % 8)
            ->addWidget(std::move(makeEventPartWidget("text-wrap rounded-bottom border-top-0")));
    }
}

std::unique_ptr<Wt::WContainerWidget> EventW::makeEventPartWidget(std::string style_class) {
    auto eventWidget = std::make_unique<Wt::WPushButton>(title_);
    eventWidget->decorationStyle().setBackgroundColor(color_);
    eventWidget->setStyleClass("btn btn-sm btn-light rounded-0 " + style_class);
    eventWidget->setId("event" + std::to_string(id_));
    auto eventContainer = std::make_unique<Wt::WContainerWidget>();
    eventContainer->addWidget(std::move(eventWidget));
    return eventContainer;
}