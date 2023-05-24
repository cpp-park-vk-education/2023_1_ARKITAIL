#include "options_w.hpp"

OptionsW::OptionsW() {}

Wt::Signal<Action>& OptionsW::selectedOption() {
    return select_option_;
}
void OptionsW::addSignal(int item_index, Action action) {
    itemAt(item_index)->triggered().connect([=] {
        select_option_.emit(action);
    });
}
