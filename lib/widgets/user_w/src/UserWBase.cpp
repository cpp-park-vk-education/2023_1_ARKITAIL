#include "UserWBase.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WText.h>

#include <memory>

UserWBase::UserWBase(const User& user) :
    avatar_(),
    description_() {

    setMinimumSize(Wt::WLength(400), Wt::WLength::Auto);
    addStyleClass("rounded p-3 border border-4 mt-2 mb-2 me-2");

    auto layout = setLayout(std::make_unique<Wt::WHBoxLayout>());
    avatar_ = layout->addWidget(std::make_unique<Wt::WImage>());
    auto text_block = layout->addWidget(std::make_unique<Wt::WContainerWidget>(), 1);
    nickname_block_ = text_block->addWidget(std::make_unique<Wt::WContainerWidget>());
    description_ = text_block->addWidget(std::make_unique<Wt::WText>(user.description));

}
