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
#include <Wt/WInteractWidget.h>
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

#include "main_p.hpp"
#include "navbar_w.hpp"
#include "other_p.hpp"

using std::cout, std::endl;

// ------------------

// ----------------------
class CalendulaApplication : public Wt::WApplication {
  public:
    CalendulaApplication(const Wt::WEnvironment &env);
    ~CalendulaApplication() { std::cout << "Calendula dead" << std::endl; }

  private:
    Wt::WBorderLayout *layout;
    NavbarW *navigation;
};

CalendulaApplication::CalendulaApplication(const Wt::WEnvironment &env) : WApplication(env) {
    setTitle("Calendula");
    setTheme(std::make_unique<Wt::WBootstrap5Theme>());
    useStyleSheet("/style/style.css");
    // setTheme(std::make_unique<Wt::WCssTheme>("polished"));
    // setInternalPath("/Calendula", true);

    auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    layout = container->setLayout(std::make_unique<Wt::WBorderLayout>());

    navigation = layout->addWidget(std::make_unique<NavbarW>(), Wt::LayoutPosition::North);
    navigation->addCalendar(std::make_unique<MainP>());
    navigation->addProfile(std::make_unique<OtherP>());
    navigation->addSearch(std::make_unique<Wt::WText>("Поиск"));

    auto item = std::make_unique<Wt::WText>("Footer");
    layout->addWidget(std::move(item), Wt::LayoutPosition::South);

    auto x = std::make_unique<Wt::WContainerWidget>();
    x->setDraggable("WContainerWidget");
    x->setStyleClass("");
    x->addWidget(std::make_unique<Wt::WText>("tytyty"));
    root()->addWidget(std::move(x));
}

int main(int argc, char **argv) {
    return Wt::WRun(argc, argv,
                    [](const Wt::WEnvironment &env) { return std::make_unique<CalendulaApplication>(env); });
}
