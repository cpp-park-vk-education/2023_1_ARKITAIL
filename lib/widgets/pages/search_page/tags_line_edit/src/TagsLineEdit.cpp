#include "TagsLineEdit.hpp"

#include <Wt/WLineEdit.h>

#include <memory>

#include "ItemsContainerW.hpp"
#include "Managers.hpp"
#include "RemovableItemW.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"

TagsLineEdit::TagsLineEdit() :
    Wt::WContainerWidget(),
    line_edit_(addWidget(std::make_unique<Wt::WLineEdit>())),
    tags_(addWidget(std::make_unique<ItemsContainerW<Tag>>())),
    added_(),
    removed_() {
    line_edit_->addStyleClass("mt-3");
    auto cm = SessionScopeMap::instance().get()->connections_mediator();
}

void TagsLineEdit::appendItem(const Tag& tag) {
    if (!tags_->hasItem(tag.id)){
        auto item = std::make_unique<RemovableItemW<Tag>>(tag.id, tag.name, tag);

        item->item_clicked()->connect([this, tag]() {
            this->removed_.emit(tag);
        });

        tags_->addItem(std::move(item));

        added_.emit(tag);
    }
    
}
