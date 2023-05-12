#include "options_w.hpp"

OptionsW::OptionsW() {
    addStyleClass("inline-block");
    options_button_ = addWidget(std::make_unique<Wt::WPushButton>("•••"));
    options_button_->addStyleClass("p-1 py-0 inline-block border-0 btn-light");
    popup_ = addWidget(std::make_unique<Wt::WPopupMenu>());
}