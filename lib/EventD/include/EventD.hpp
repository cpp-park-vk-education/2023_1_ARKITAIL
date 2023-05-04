#pragma once
#include <Wt/WBorderLayout.h>
#include <Wt/WContainer.h>
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedW.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>

#include "CommentsContainerW.hpp"

class EventD : public Wt::WDialog {
  public:
    EventD();
    ~EventD() = default;

  private:
    int id;
    Wt::WText* title_;
    Wt::WPushButton* button_edit_;
    Wt::WString dates_;
    Wt::WTextArea* description_;
    Wt::WStackedW* image_stack_;
    Wt::WBorderLayout* icons_container_;
    CommentsContainerW* comments_container_;
    Wt::WContainer* resource_container_;

    void openComments();
    void edit();
};
