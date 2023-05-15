#include "options_w.hpp"

OptionsW::OptionsW() {}

Wt::Signal<Action>& OptionsW::selectedOption() { return select_option_; }