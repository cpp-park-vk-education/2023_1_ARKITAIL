#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WCssStyleSheet.h>
#include <Wt/WCssTheme.h>
#include <Wt/WDate.h>
#include <Wt/WGridLayout.h>
#include <Wt/WIconPair.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WMessageBox.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPopupMenuItem.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WString.h>
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>
#include <Wt/WTree.h>
#include <Wt/WTreeNode.h>

#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "calendar.hpp"
#include "navigation.hpp"
#include "private_calendar.hpp"
#include "public_calendar.hpp"

using std::cout, std::endl;

// ------------------

// ----------------------
class CalendulaApplication : public Wt::WApplication {
  public:
    CalendulaApplication(const Wt::WEnvironment &env);
    ~CalendulaApplication() { std::cout << "Calendula dead" << std::endl; }

  private:
    Wt::WBorderLayout *layout;
    Navigation *navigation;
};

CalendulaApplication::CalendulaApplication(const Wt::WEnvironment &env) : WApplication(env) {
    setTitle("Calendula");
    setTheme(std::make_unique<Wt::WBootstrap5Theme>());
    useStyleSheet("/resources/style/style.css");
    // setTheme(std::make_unique<Wt::WCssTheme>("polished"));
    // setInternalPath("/Calendula", true);

    auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    layout = container->setLayout(std::make_unique<Wt::WBorderLayout>());

    // -----------------начало

    navigation = layout->addWidget(std::make_unique<Navigation>(), Wt::LayoutPosition::North);
    navigation->addPublicCalendar(std::make_unique<PublicCalendar>());
    navigation->addProfile(std::make_unique<Wt::WText>("Профиль"));
    navigation->addPrivateCalendar(std::make_unique<Wt::WText>("Приватный календарь"));

    // -------------- дерево

    auto item = std::make_unique<Wt::WText>("Footer");
    layout->addWidget(std::move(item), Wt::LayoutPosition::South);
}

int main(int argc, char **argv) {
    return Wt::WRun(argc, argv,
                    [](const Wt::WEnvironment &env) { return std::make_unique<CalendulaApplication>(env); });
}
