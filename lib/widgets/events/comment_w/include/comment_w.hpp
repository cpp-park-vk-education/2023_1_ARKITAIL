#pragma once

#include <Wt/WAnchor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class CommentW : public Wt::WContainerWidget {
  public:
    CommentW(std::string text);
    ~CommentW() = default;

  private:
    Wt::WImage* author_img_;
    Wt::WAnchor* author_;
    Wt::WText* text_;
    Wt::WPushButton* button_edit_;
    Wt::WPushButton* delete_button_;
};
