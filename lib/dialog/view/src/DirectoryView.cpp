#include "DirectoryView.hpp"

#include <memory>

#include <Wt/WLineEdit.h>
#include <Wt/WTemplateFormView.h>
#include <Wt/WTextArea.h>

#include "DirectoryModel.hpp"

namespace dialog {
std::shared_ptr<DirectoryModel> DirectoryView::model() const {
  return model_;
}

// по умолчанию directory = nullptr
DirectoryView::DirectoryView(DirectorySptr directory)
    : Wt::WTemplateFormView(Wt::WString::tr("directory")),
      model_(std::make_shared<DirectoryModel>(directory)) {
  InitializeName();
  InitializeDescription();

  bindEmpty("validation-status");

  updateView(model_.get());
}

void DirectoryView::InitializeName() {
  setFormWidget(DirectoryModel::kName, std::make_unique<Wt::WLineEdit>());
}

void DirectoryView::InitializeDescription() {
  auto description = std::make_unique<Wt::WTextArea>();
  description->setRows(10);
  setFormWidget(DirectoryModel::kDescription, std::move(description));
}
} // namespace dialog
