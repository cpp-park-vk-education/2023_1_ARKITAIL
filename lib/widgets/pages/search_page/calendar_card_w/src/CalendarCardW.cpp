#include "CalendarCardW.hpp"

#include <Wt/WText.h>

#include <memory>
#include <vector>

#include "Calendar.hpp"
#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "TagW.hpp"
#include "User.hpp"
#include "UserAnchorW.hpp"

CalendarCardW::CalendarCardW() :
    title_(),
    descriptions_(),
    tags_(),
    username_(),
    node_() {}

CalendarCardW::CalendarCardW(const User& user, CalendarSptr calendar,
                             const std::vector<Tag>& tags) :
    title_(addWidget(std::make_unique<Wt::WAnchor>(
        Wt::WLink(Wt::LinkType::InternalPath, "/other_calendar"), calendar->summary))),
    username_(addWidget(std::make_unique<UserAnchorW>(user))),
    descriptions_(addWidget(std::make_unique<Wt::WText>(
        "<b>Описание:</b> " + ((calendar->description.empty()) ? " — " : calendar->description)))),
    tags_(),
    node_() {
    auto ss = SessionScopeMap::instance().get();
    auto mng = ss->managers();
    node_ = mng->node_manager()->get(calendar->node_id);

    addStyleClass("rounded p-3 border border-4 mt-2 p-0");

    title_->addStyleClass("d-block fs-4 fw-bolder link-success text-decoration-none hover");
    title_->clicked().connect([&] {
        calendar_clicked_.emit(node_);
    });

    ss->connections_mediator()->set_tree_root.add_sender(&calendar_clicked_);

    descriptions_->addStyleClass("d-block mb-1");

    for (auto tag : tags) {
        tags_.push_back(addWidget(std::make_unique<TagW>(tag)));
    }

}