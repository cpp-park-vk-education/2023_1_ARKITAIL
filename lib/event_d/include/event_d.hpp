#pragma once

#include <memory.h>

#include <Wt/WDialog.h>
#include <Wt/WGlobal.h>

#include "event.hpp"
#include "event_settings_fv.hpp"

class EventD : public Wt::WDialog {
 public:
  EventD();

  void Show(std::unique_ptr<Event> event = nullptr);

  Wt::Signal<std::unique_ptr<Event>>& EventCreated();
  Wt::Signal<std::unique_ptr<Event>>& EventEdited();
 private:
  EventSettingsFV* event_settings;

  Wt::WPushButton* create_;
  Wt::WPushButton* cancel_;

  Wt::Signal<std::unique_ptr<Event>> event_created_;
  Wt::Signal<std::unique_ptr<Event>> event_edited_;
};
