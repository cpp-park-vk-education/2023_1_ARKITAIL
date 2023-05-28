#pragma once

#include <Wt/WDialog.h>
#include <Wt/WTabWidget.h>

#include "Calendar.hpp"
#include "ITreeNode.hpp"

namespace dialog {
class CreateCalendarDialog : public Wt::WDialog {
 public:
  CreateCalendarDialog(ITreeNode* node);

  Wt::Signal<NodeSptr>& node_created();
 private:
  void ChooseHandler();

  void HandleSettings();
  void HandleImport();

  Wt::Signal<NodeSptr> node_created_;

  Wt::WTabWidget* tabs_;
  ITreeNode* node_;
};
} // namespace dialog
