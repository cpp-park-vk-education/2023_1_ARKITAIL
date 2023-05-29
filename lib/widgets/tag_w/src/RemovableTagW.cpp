#include "RemovableTagW.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

#include "Tag.hpp"
#include "TagW.hpp"

RemovableTagW::RemovableTagW(Tag tag) :
    TagW(tag) {
    remove_button_ = addWidget(std::make_unique<Wt::WPushButton>());
    remove_button_->addStyleClass("btn-close");
    remove_button_->clicked().connect([=]() {
        parent()->removeChild(this);
    });
}
