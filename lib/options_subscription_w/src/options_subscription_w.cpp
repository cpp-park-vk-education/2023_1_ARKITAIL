#include "options_subscription_w.hpp"

OptionsSubscriptionW::OptionsSubscriptionW() {
    addItem("Отписаться")->triggered().connect([=] { select_option_.emit(UNSUBSCRIBE); });
}