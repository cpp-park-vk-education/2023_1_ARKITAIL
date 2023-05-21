#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>

enum Action {
    REMOVE = 0,
    SUBSCRIBE,
    UNSUBSCRIBE,
    GO_TO_AUTHOR,
    EDIT,
    ADD_CALENDAR,
    ADD_DIRECTORY
};

class OptionsW : public Wt::WPopupMenu {
  public:
    OptionsW();
    ~OptionsW() = default;

    Wt::Signal<Action>& selectedOption();

    OptionsW* addOptionRemove();
    OptionsW* addOptionEdit();
    OptionsW* addOptionAddCalendar();
    OptionsW* addOptionAddDirectory();
    OptionsW* addOptionSubscribe();
    OptionsW* addOptionUnsubscribe();

    Wt::Signal<Action> select_option_;
};
