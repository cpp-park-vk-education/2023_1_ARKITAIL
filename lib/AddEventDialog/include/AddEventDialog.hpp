#pragma once
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WDateEdit.h>
#include <Wt/WDateValidator.h>
#include <Wt/WDialog.h>
#include <Wt/WEnvironment.h>
#include <Wt/WLabel.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WTime.h>
#include <Wt/WTimeEdit.h>
#include <Wt/WTimeValidator.h>
#include <Wt/WValidator.h>

#include <memory>

class AddEventDialog : public Wt::WContainerWidget {
  public:
    AddEventDialog();
    ~AddEventDialog() = default;

  private:
    Wt::WLineEdit* title_line_;
    std::shared_ptr<Wt::WLengthValidator> title_validator_;
    Wt::WCheckBox* check_box_all_day_;
    std::shared_ptr<Wt::WButtonGroup> periodicity_radio_group_;
    Wt::WDateEdit* begin_date_line_;
    Wt::WTimeEdit* begin_time_line_;
    Wt::WDateEdit* end_date_line_;
    Wt::WTimeEdit* end_time_line_;
    std::shared_ptr<Wt::WDateValidator> date_validator_;
    std::shared_ptr<Wt::WTimeValidator> time_validator_;
    Wt::WPushButton* save_button_;
};
