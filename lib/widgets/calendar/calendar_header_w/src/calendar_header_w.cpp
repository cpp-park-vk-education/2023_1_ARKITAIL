#include "calendar_header_w.hpp"

#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>

#include <memory>

#include "Event.hpp"
#include "time_utils.hpp"

CalendarHeaderW::CalendarHeaderW() :
    today_button_(),
    prev_button_(),
    next_button_(),
    calendar_title_(),
    container_option_range_(),
    option_range_(),

    events_range_changed(),
    change_selected_date_(),
    change_range_(),

    selected_date_(Wt::WDate(std::chrono::system_clock::now())),
    range_(Range::WEEK) {}

Wt::WString CalendarHeaderW::makeTitle() {
    if (range_ == Range::DAY) {
        return selected_date_.toString("d MMMM");
    }
    return selected_date_.toString("MMMM yyyy");
}

void CalendarHeaderW::addStyle() {
    addStyleClass("d-flex flex-column flex-lg-row justify-content-center align-items-center my-3");
    container_option_range_->addStyleClass("d-flex row");
    today_button_->addStyleClass("mx-2 btn-light");
    prev_button_->addStyleClass("mx-1 btn-light");
    next_button_->addStyleClass("mx-2 btn-light");
    calendar_title_->addStyleClass("mx-3 h2");
    option_range_->addStyleClass("col mx-3");
}

void CalendarHeaderW::setRange() {
    range_ = Range(option_range_->currentIndex());
    calendar_title_->setText(makeTitle());
    change_range_.emit(range_);
    emitDates();
}

Wt::WDate CalendarHeaderW::switchSelectedDate(SwitchingDirection direction) {
    if (direction == SwitchingDirection::TODAY) {
        return selected_date_ = Wt::WDate(std::chrono::system_clock::now());
    }
    switch (range_) {
        case Range::DAY:
            return selected_date_ = Wt::WDate(selected_date_.addDays(direction));

        case Range::WEEK:
            return selected_date_ =
                       Wt::WDate(selected_date_.addDays(direction * TimeInterval::DAYS_IN_WEEK));

        case Range::MONTH:
            return selected_date_ = Wt::WDate(selected_date_.addMonths(direction));
    }
    return selected_date_;
}

void CalendarHeaderW::switchToToday() {
    calendar_title_->setText(makeTitle());
    switchSelectedDate(SwitchingDirection::TODAY);
    emitDates();
}

void CalendarHeaderW::switchToPrev() {
    switchSelectedDate(SwitchingDirection::BACK);
    calendar_title_->setText(makeTitle());
    emitDates();
}

void CalendarHeaderW::switchToNext() {
    switchSelectedDate(SwitchingDirection::FORWARD);
    calendar_title_->setText(makeTitle());  
    emitDates();
}

Wt::Signal<Wt::WDate, Wt::WDate>& CalendarHeaderW::selectedDateChanged() {
    return selected_date_changed_;
}

Wt::Signal<Range>& CalendarHeaderW::rangeChanged() {
    return change_range_;
}

void CalendarHeaderW::setSelectedDate(Wt::WDate new_date) {
    selected_date_ = new_date;
}

void CalendarHeaderW::setValueRange(Range range) {
    range_ = range;
}

CalendarHeaderW* CalendarHeaderW::addButtons() {
    auto button_box = addNew<Wt::WContainerWidget>();
    button_box->addStyleClass("my-2 me-2 my-lg-0 d-flex justify-content-center");
    today_button_ = button_box->addNew<Wt::WPushButton>("Сегодня");
    prev_button_ = button_box->addNew<Wt::WPushButton>("<");
    next_button_ = button_box->addNew<Wt::WPushButton>(">");
    calendar_title_ = button_box->addNew<Wt::WText>(makeTitle());

    container_option_range_ = addNew<Wt::WContainerWidget>();

    option_range_ = container_option_range_->addNew<Wt::WComboBox>();
    option_range_->addItem("Месяц");
    option_range_->addItem("Неделя");
    option_range_->addItem("День");
    option_range_->setCurrentIndex(Range::WEEK);
    addStyle();
    return this;
}

CalendarHeaderW* CalendarHeaderW::addConnections() {
    today_button_->clicked().connect(this, &CalendarHeaderW::switchToToday);
    prev_button_->clicked().connect(this, &CalendarHeaderW::switchToPrev);
    next_button_->clicked().connect(this, &CalendarHeaderW::switchToNext);
    option_range_->changed().connect(this, &CalendarHeaderW::setRange);
    return this;
}

void CalendarHeaderW::emitDates() {
    Wt::WDate date1, date2;
    switch (range_) {
        case Range::DAY:
            date1 = selected_date_;
            date2 = selected_date_;
            break;
        case Range::WEEK:
            date1 = selected_date_.addDays(1 - selected_date_.dayOfWeek());
            date2 = selected_date_.addDays(TimeInterval::DAYS_IN_WEEK - selected_date_.dayOfWeek());
            break;
        case Range::MONTH:
            auto first_day_of_month = Wt::WDate(selected_date_.year(), selected_date_.month(), 1);
            date1 = first_day_of_month.addDays(1 - first_day_of_month.dayOfWeek());
            date2 = date1.addDays(5 * TimeInterval::DAYS_IN_WEEK);
            break;
    }
    std::cout << "\nотправляется сигнал из хедера с двумя датами в дерево, то есть "
                 "selected_date_changed_ emit\n"
              << std::endl;
    selected_date_changed_.emit(date1, date2);
}
