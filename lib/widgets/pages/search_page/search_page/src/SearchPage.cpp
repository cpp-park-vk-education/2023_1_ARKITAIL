#include "SearchPage.hpp"

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include <memory>

#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"
#include "TagsLineEdit.hpp"
#include "UsersLineEdit.hpp"

SearchP::SearchP() :
    users_(addWidget(std::make_unique<UsersLineEdit>())),
    tags_(addWidget(std::make_unique<TagsLineEdit>())),
    hint_(addWidget(std::make_unique<Wt::WText>())),
    found_(addWidget(std::make_unique<CalendarCardContainerW>())),
    searcher_() {
    users_->parseItem("ХУЙ");
    users_->parseItem("ХУЙ");
    users_->parseItem("ХУЙ");
    users_->parseItem("ХУЙ");

    auto ss = SessionScopeMap::instance().get();

    auto cm = ss->connections_mediator();
    cm->search_tag.add_receiver(tags_, &TagsLineEdit::appendItem);

    auto mgr = ss->managers();
    auto c = mgr->calendar_manager()->get(7);
    found_->init(std::vector<CalendarSptr>{c});
}

void SearchP::search() {}
