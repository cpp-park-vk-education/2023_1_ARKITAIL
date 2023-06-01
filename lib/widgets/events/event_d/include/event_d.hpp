#pragma once
#include <Wt/WBorderLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>

#include "comments_container_w.hpp"

class EventD : public Wt::WDialog {
  public:
    EventD(size_t id, std::string title);
    ~EventD() = default;

    Wt::Signal<const std::string&, size_t> event_edited_;
  private:
    size_t id_;
    Wt::WPushButton* button_edit_;
    Wt::WText* dates_;
    Wt::WText* description_;
    Wt::WPushButton* edit_button_;
    // Wt::WImage* image_;
    // Wt::WStackedWidget* image_stack_;
    // Wt::WImage* comments_button_;
    // Wt::WBorderLayout* icons_container_;
    // CommentsContainerW* comments_container_;
    // Wt::WContainerWidget* resource_container_;

    void edit();
};
