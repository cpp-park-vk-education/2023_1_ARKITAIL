#pragma once

#include <Wt/WDialog.h>

#include "Directory.hpp"
#include "DirectoryView.hpp"

namespace dialog {
class EditDirectoryDialog : public Wt::WDialog {
 public:
  EditDirectoryDialog() = delete;
  EditDirectoryDialog(DirectorySptr directory);

  Wt::Signal<DirectorySptr>& directory_updated();
 private:
  void HandleInput();

  Wt::Signal<DirectorySptr> directory_updated_;

  DirectoryView* view_;
};
} // namespace dialog
