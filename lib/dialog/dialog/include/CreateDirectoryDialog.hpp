#pragma once

#include <Wt/WDialog.h>

#include "Directory.hpp"
#include "DirectoryView.hpp"
#include "ITreeNode.hpp"

namespace dialog {
class CreateDirectoryDialog : public Wt::WDialog {
 public:
  CreateDirectoryDialog(ITreeNode* node);

  Wt::Signal<NodeSptr>& node_created();
 private:
  void HandleInput();

  Wt::Signal<NodeSptr> node_created_;

  DirectoryView* view_;
  ITreeNode* node_;
};
} // namespace dialog
