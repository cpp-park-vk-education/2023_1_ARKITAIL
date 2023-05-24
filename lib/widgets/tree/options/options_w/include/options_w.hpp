#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>

enum Action {
    REMOVE,
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

    void addSignal(int item_index, Action action);

    Wt::Signal<Action> select_option_;
};
