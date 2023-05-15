#pragma once

#include <Wt/WAnchor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLink.h>
#include <Wt/WSignal.h>

#include <string>

class PageWidget : public Wt::WContainerWidget {
  public:
    PageWidget();

    void trigger();
    void triggered(int);

  private:
    void init();

    Wt::Signal<int> triggered_;
};
