#include "calendar.hpp"

Calendar::Calendar() : range(week) {
    selected_date = std::make_unique<Wt::WDate>(std::chrono::system_clock::now());
    addNavbar();
    auto table = std::make_unique<Wt::WTable>();
    table_ = table.get();
    addWidget(std::move(table));
    updateCalendar();
    addStyles();
}

void Calendar::updateCalendar() {
    table_->clear();
    //  запрос событий нужного промежутка (range, selected_date)
    //  !!!они будут частично или полностью принадлежать промежутку
    std::vector<Event> events = {
        Event(0, "Event0 цыцы ыцыцыцыцы вувув", Wt::WColor(200, 50, 50, 50),
              Wt::WDateTime(Wt::WDate(2023, 4, 20), Wt::WTime(12, 45)),
              Wt::WDateTime(Wt::WDate(2023, 4, 20), Wt::WTime(14, 0))),
        Event(1, "Event1", Wt::WColor(50, 20, 220, 50), Wt::WDateTime(Wt::WDate(2023, 4, 20), Wt::WTime(12, 45)),
              Wt::WDateTime(Wt::WDate(2023, 4, 26), Wt::WTime(14, 0))),
        Event(2, "Event2", Wt::WColor(250, 20, 220, 50), Wt::WDateTime(Wt::WDate(2023, 4, 25), Wt::WTime(12, 45)),
              Wt::WDateTime(Wt::WDate(2023, 4, 30), Wt::WTime(14, 0)))};

    switch (range) {
        case day:
            break;
        case week:
            table_->setHeaderCount(1);
            table_->setHeaderCount(1, Wt::Orientation::Vertical);
            table_->addStyleClass("week");
            makeHeaderTime();
            makeHeaderWeek();
            for (auto &&event : events) {
                event.makeEventWidgets(table_, *(selected_date.get()));
            }
            break;
        case month:
            table_->setHeaderCount(1);
            table_->addStyleClass("week");
            makeHeaderWeek();
            break;
    }
    calendar_title->setText(makeTitle());
}

Wt::WString Calendar::makeTitle() { return selected_date->toString("MMMM yyyy"); }

void Calendar::addNavbar() {
    auto calendar_navbar = addNew<Wt::WContainerWidget>();
    calendar_navbar->addStyleClass("d-flex flex-column flex-lg-row justify-content-center align-items-center my-3");

    auto button_box = calendar_navbar->addNew<Wt::WContainerWidget>();
    button_box->addStyleClass("my-2 me-2 my-lg-0 d-flex justify-content-center");
    today_button = button_box->addNew<Wt::WPushButton>("Сегодня");
    prev_day_button = button_box->addNew<Wt::WPushButton>("<");
    next_day_button = button_box->addNew<Wt::WPushButton>(">");

    calendar_title = button_box->addNew<Wt::WText>(makeTitle());

    auto container_option_range = calendar_navbar->addNew<Wt::WContainerWidget>();
    container_option_range->addStyleClass("d-flex ms-3 row");
    option_range = container_option_range->addNew<Wt::WComboBox>();
    option_range->addItem("Месяц");
    option_range->addItem("Неделя");
    option_range->addItem("День");
    option_range->setCurrentIndex(1);

    button_add_event = container_option_range->addNew<Wt::WPushButton>("Добавить событие");

    addSignals();
}

void Calendar::addSignals() {
    today_button->clicked().connect(this, &Calendar::today);
    prev_day_button->clicked().connect(this, &Calendar::prevDay);
    next_day_button->clicked().connect(this, &Calendar::nextDay);
    option_range->changed().connect(bindSafe([this] { setRange(Range(option_range->currentIndex())); }));

    auto c = addWidget(std::make_unique<Wt::WContainerWidget>());
    button_add_event->clicked().connect([=] { Calendar::showAddEventModal(c); });
}

void Calendar::showAddEventModal(Wt::WObject *owner) {
    Wt::WDialog *dialog = owner->addChild(std::make_unique<Wt::WDialog>("Добавить событие"));

    dialog->setClosable(true);
    dialog->rejectWhenEscapePressed();

    dialog->contents()->addStyleClass("form-group");

    Wt::WLineEdit *title = dialog->contents()->addNew<Wt::WLineEdit>();
    title->setPlaceholderText("Название");
    auto title_validator = std::make_shared<Wt::WLengthValidator>(1, 15);  // какая длина у заголовка?
    title_validator->setMandatory(true);
    title->setValidator(title_validator);

    Wt::WTextArea *desc = dialog->contents()->addNew<Wt::WTextArea>();
    desc->setPlaceholderText("Описание");
    auto desc_validator = std::make_shared<Wt::WLengthValidator>();
    desc_validator->setMaximumLength(500);
    desc->setValidator(desc_validator);

    Wt::WCheckBox *allDay = dialog->contents()->addNew<Wt::WCheckBox>("Весь день");

    auto date_validator = std::make_shared<Wt::WDateValidator>();
    date_validator->setMandatory(true);
    date_validator->setFormat("dd/MM/yyyy");
    date_validator->setInvalidNotADateText(
        "You should enter a date in the format "
        "\"dd/MM/yyyy\"!");

    auto begin_container = dialog->contents()->addNew<Wt::WContainerWidget>();

    Wt::WDateEdit *begin_date = begin_container->addNew<Wt::WDateEdit>();
    begin_date->setPlaceholderText("Начало");
    begin_date->setValidator(date_validator);

    auto time_validator = std::make_shared<Wt::WTimeValidator>("hh:mm");
    time_validator->setMandatory(true);

    Wt::WTimeEdit *begin_time = begin_container->addNew<Wt::WTimeEdit>();
    begin_time->setFormat("hh:mm");
    begin_time->setPlaceholderText("Начало");
    begin_time->setValidator(time_validator);

    auto end_container = dialog->contents()->addNew<Wt::WContainerWidget>();

    Wt::WDateEdit *end_date = end_container->addNew<Wt::WDateEdit>();
    end_date->setPlaceholderText("Начало");
    end_date->setValidator(date_validator);

    Wt::WTimeEdit *end_time = end_container->addNew<Wt::WTimeEdit>();
    end_time->setFormat("hh:mm");
    end_time->setPlaceholderText("Начало");
    end_time->setValidator(time_validator);

    allDay->changed().connect([=] {
        begin_time->toggleStyleClass("visually-hidden", allDay->isChecked());
        end_time->toggleStyleClass("visually-hidden", allDay->isChecked());
    });

    Wt::WPushButton *save = dialog->footer()->addNew<Wt::WPushButton>("Save");
    save->setDefault(true);
    if (wApp->environment().ajax()) save->disable();

    title->keyWentUp().connect([=] { save->setDisabled(title->validate() != Wt::ValidationState::Valid); });

    save->clicked().connect([=] {
        if (title->validate() == Wt::ValidationState::Valid && begin_date->validate() == Wt::ValidationState::Valid &&
            end_date->validate() == Wt::ValidationState::Valid &&
            begin_time->validate() == Wt::ValidationState::Valid && end_time->validate() == Wt::ValidationState::Valid)
            dialog->accept();

        // отправить Сене
    });

    dialog->show();
}

void Calendar::addEvent() {
    // кинуть запрос на добавление
    updateCalendar();
}

void Calendar::today() {
    selected_date = std::make_unique<Wt::WDate>(std::chrono::system_clock::now());
    updateCalendar();
}

void Calendar::prevDay() {
    switch (range) {
        case day:
            selected_date = std::make_unique<Wt::WDate>(selected_date->addDays(-1));
            break;
        case week:
            selected_date = std::make_unique<Wt::WDate>(selected_date->addDays(-7));
            break;
        case month:
            selected_date = std::make_unique<Wt::WDate>(selected_date->addMonths(-1));
            break;
    }
    updateCalendar();
}

void Calendar::nextDay() {
    switch (range) {
        case day:
            selected_date = std::make_unique<Wt::WDate>(selected_date->addDays(1));
            break;
        case week:
            selected_date = std::make_unique<Wt::WDate>(selected_date->addDays(7));
            break;
        case month:
            selected_date = std::make_unique<Wt::WDate>(selected_date->addMonths(1));
            break;
    }
    updateCalendar();
}

void Calendar::setRange(Range new_range) {
    range = new_range;
    updateCalendar();
}

void Calendar::activateToday(int begin_week_day) {
    auto today_day = std::make_unique<Wt::WDate>(std::chrono::system_clock::now());
    if (selected_date->month() == today_day->month() && today_day->day() >= begin_week_day &&
        today_day->day() <= begin_week_day + 7) {
        // table_->elementAt(0, today_day->dayOfWeek())->decorationStyle().setBackgroundColor(Wt::WColor(50, 255, 0,
        // 80));   задать свой цвет сегодняшней даты
        table_->elementAt(0, today_day->dayOfWeek() + range - 1)->addStyleClass("table-success");
    }
}

void Calendar::makeHeaderWeek() {
    selected_date = std::make_unique<Wt::WDate>(selected_date->addDays(-selected_date->dayOfWeek() + 1));
    auto begin_week_day = std::make_unique<Wt::WDate>(selected_date->addDays(0));
    activateToday(begin_week_day->day());

    for (int i{1}; auto &&weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, range - 1 + i)->addNew<Wt::WText>(weekday);
        table_->elementAt(0, range - 1 + i++)->addNew<Wt::WText>(", " + std::to_string(begin_week_day->day()));
        begin_week_day = std::make_unique<Wt::WDate>(begin_week_day->addDays(1));
    }
    table_->insertRow(1);
}

void Calendar::makeHeaderTime() {
    for (unsigned i = 0; i < 24; ++i) {
        table_->elementAt(i + 1, 0)->addNew<Wt::WText>(Wt::WString(i < 10 ? "0{1}:00" : "{1}:00").arg(i));
    }
}

void Calendar::addStyles() {
    addStyleClass("container calendar");
    today_button->addStyleClass("mx-2 btn-light");
    prev_day_button->addStyleClass("mx-1 btn-light");
    next_day_button->addStyleClass("mx-2 btn-light");
    calendar_title->addStyleClass("mx-3 h2");
    option_range->addStyleClass("col mx-3");
    button_add_event->addStyleClass("col mx-3");
    table_->setWidth(Wt::WLength("100%"));
    table_->addStyleClass("table table-bordered table-sm d-block");
}
