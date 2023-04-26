#include "navigation.hpp"

Navigation::Navigation() {
    navigation = addNew<Wt::WNavigationBar>();
    navigation->setTitle("Calendula", "/");

    contents_stack = addNew<Wt::WStackedWidget>();
    auto leftMenu = std::make_unique<Wt::WMenu>(contents_stack);
    left_menu_ = navigation->addMenu(std::move(leftMenu));

    auto searchResult = std::make_unique<Wt::WText>("Тут будут профили");
    searchResult_ = searchResult.get();

    profile = addLink("My Profile", "/profile");

    private_calendar = addLink("Private calendar", "/private");

    public_calendar = addLink("Public calendar", "/public");

    // Search
    profiles = addLink("Profiles", "/profiles");
    addProfiles(std::move(searchResult));
    auto search_linePtr = std::make_unique<Wt::WLineEdit>();
    search_line = search_linePtr.get();
    search_line->setPlaceholderText("Enter a search profile");
    navigation->addSearch(std::move(search_linePtr));

    auto exitPtr = std::make_unique<Wt::WPushButton>("Logout");
    exit = exitPtr.get();
    navigation->addWidget(std::move(exitPtr));

    addSignals();
    addStyle();
}

Wt::WMenuItem *Navigation::addLink(const std::string &iconPath, const std::string &path) {
    auto tmp = left_menu_->addItem(iconPath);
    tmp->setLink(Wt::WLink(Wt::LinkType::InternalPath, path));
    return tmp;
}

void Navigation::addProfile(std::unique_ptr<Wt::WWidget> content) { profile->setContents(std::move(content)); }

void Navigation::addPrivateCalendar(std::unique_ptr<Wt::WWidget> content) {
    private_calendar->setContents(std::move(content));
}

void Navigation::addPublicCalendar(std::unique_ptr<Wt::WWidget> content) {
    public_calendar->setContents(std::move(content));
}

void Navigation::addProfiles(std::unique_ptr<Wt::WWidget> content) { profiles->setContents(std::move(content)); }

void Navigation::addSignals() {
    profiles->clicked().connect([=] { searchResult_->setText("Profiles"); });
    search_line->enterPressed().connect(this, &Navigation::search);
    exit->clicked().connect(this, &Navigation::logout);
}

void Navigation::addStyle() {
    setStyleClass("top-0");
    navigation->setResponsive(true);
    navigation->addStyleClass("navbar navbar-light bg-light navbar-expand-lg");
    contents_stack->addStyleClass("contents");
    left_menu_->addStyleClass("me-auto");
    exit->addStyleClass("ms-2");
}

void Navigation::search() {
    left_menu_->select(profiles);
    // должен вызываться метод поиска пользователя search_line->text() у контента
    searchResult_->setText(Wt::WString("Не знаю какого-то там {1} (((").arg(search_line->text()));
    Wt::WApplication::instance()->setInternalPath("/search", true);
    search_line->setText("");
}

void Navigation::logout() {
    // выходим
}
