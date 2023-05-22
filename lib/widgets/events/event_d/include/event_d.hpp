#pragma once
#include <Wt/WBorderLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>

#include "comments_container_w.hpp"

class EventD : public Wt::WDialog {
  public:
    EventD(int id, std::string title);
    ~EventD() = default;

  private:
    int id_;
    Wt::WPushButton* button_edit_;
    Wt::WString dates_;
    Wt::WTextArea* description_;
    Wt::WImage* image_;
    // Wt::WStackedWidget* image_stack_;
    Wt::WImage* comments_button_;
    // Wt::WBorderLayout* icons_container_;
    CommentsContainerW* comments_container_;
    Wt::WContainerWidget* resource_container_;

    void openComments();
    void edit();
};
