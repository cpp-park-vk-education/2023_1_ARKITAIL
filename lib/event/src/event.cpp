#include "event.hpp"

std::unique_ptr<Wt::WContainerWidget> Event::makeBigEventtWidget(std::string style_class) {
    auto eventWidget = std::make_unique<Wt::WPushButton>(title);
    eventWidget->decorationStyle().setBackgroundColor(color);
    eventWidget->setStyleClass("btn btn-sm btn-light rounded-0 w-100 text-nowrap " + style_class);
    eventWidget->setId("event" + std::to_string(id));
    auto eventContainer = std::make_unique<Wt::WContainerWidget>();
    eventContainer->addWidget(std::move(eventWidget));
    return eventContainer;
}

std::unique_ptr<Wt::WContainerWidget> Event::makeSmallEventWidget(std::string style_class) {
    auto eventWidget = std::make_unique<Wt::WPushButton>(title);
    eventWidget->decorationStyle().setBackgroundColor(color);
    eventWidget->setStyleClass("btn btn-sm btn-light rounded-0 text-wrap " + style_class);
    eventWidget->setId("event" + std::to_string(id));
    auto eventContainer = std::make_unique<Wt::WContainerWidget>();
    eventContainer->addWidget(std::move(eventWidget));
    return eventContainer;
}

void Event::makeEventWidgets(Wt::WTable *table_, Wt::WDate beginWeek) {
    int dayWeek = begin.date().dayOfWeek();
    if (begin.date().daysTo(end.date())) {
        auto day = begin.date() > beginWeek ? begin.date() : beginWeek;
        table_->elementAt(1, day.dayOfWeek())->addWidget(std::move(makeBigEventtWidget("rounded-start border-end-0")));
        day = day.addDays(1);
        for (; day < end.date() && day < beginWeek.addDays(7); day = day.addDays(1)) {
            table_->elementAt(1, day.dayOfWeek())
                ->addWidget(std::move(makeBigEventtWidget("border-start-0 border-end-0")));
        }
        if (day <= end.date() && day < beginWeek.addDays(7))
            table_->elementAt(1, day.dayOfWeek())
                ->addWidget(std::move(makeBigEventtWidget("rounded-end border-start-0")));

    } else {
        int h = begin.time().hour();
        table_->elementAt(h + 2, dayWeek % 8)
            ->addWidget(std::move(makeSmallEventWidget("rounded-top border-bottom-0")));
        h++;
        for (; h < end.time().hour() - 1; h++) {
            table_->elementAt(h + 2, dayWeek % 8)
                ->addWidget(std::move(makeSmallEventWidget("border-top-0 border-bottom-0")));
        }
        table_->elementAt(h + 2, dayWeek % 8)
            ->addWidget(std::move(makeSmallEventWidget("rounded-bottom border-top-0")));
        // for (int h = begin.time().hour(), dayWeek = begin.date().dayOfWeek();
        //      begin.date() >= *selectedDate &&
        //      (h < end.time().hour() || (begin.date().daysTo(end.date()) && h < 24));
        //      h++) {
        //     table_->elementAt(h + 1, dayWeek % 8)->addWidget(std::move(makeEventWidget()));
        // }
        // for (int dayWeek = begin.date().dayOfWeek() + 1;
        //      dayWeek < end.date().dayOfWeek() + begin.date().daysTo(end.date()) - 1 && dayWeek <= 7; dayWeek++) {
        //     for (int h = 0; h < 24; h++) {
        //         table_->elementAt(h + 1, dayWeek % 8)->addWidget(std::move(makeEventWidget()));
        //     }
        // }
        // cout << selectedDate->daysTo(end.date()) << ' ' << selectedDate->toString() << ' ' << end.toString()
        //      << endl;
        // for (int h = 0, dayWeek = end.date().dayOfWeek();
        //      begin.date().daysTo(end.date()) && selectedDate->daysTo(end.date()) <= 7 && h < end.time().hour();
        //      h++) {
        //     table_->elementAt(h + 1, dayWeek % 8)->addWidget(std::move(makeEventWidget()));
        // }
    }
}
