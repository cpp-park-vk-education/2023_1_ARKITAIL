#pragma once

#include <memory>

#include <Wt/WTemplateFormView.h>

#include "Directory.hpp"
#include "DirectoryModel.hpp"

namespace dialog {
class DirectoryView : public Wt::WTemplateFormView {
 public:
  explicit DirectoryView(DirectorySptr directory = nullptr);

  std::shared_ptr<DirectoryModel> model() const;
 private:
  void InitializeName();
  void InitializeDescription();
  
  std::shared_ptr<DirectoryModel> model_;
};
} // namespace dialog
