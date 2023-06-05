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
    line_edit_->enterPressed().connect([this]() {
		if (!this->line_edit_->text().empty()) {
    		auto manager = SessionScopeMap::instance().get()->managers()->tag_manager();
            auto tag = manager->find(this->line_edit_->text().toUTF8());
            if (tag->id != 0) {
                this->appendItem(*tag);
            }
		}
    });
}

void TagsLineEdit::appendItem(const Tag& tag) {
    if (!tags_->hasItem(tag.name)){
        auto item = std::make_unique<RemovableItemW<Tag>>(tag.name, tag);

        item->item_clicked()->connect([this, tag]() {
            this->removed_.emit(tag);
        });

        tags_->addItem(std::move(item));

        added_.emit(tag);
    }
    
}
