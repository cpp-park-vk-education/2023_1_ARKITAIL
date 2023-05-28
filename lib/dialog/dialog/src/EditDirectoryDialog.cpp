#include "EditDirectoryDialog.hpp"

#include "Directory.hpp"
#include "DirectoryView.hpp"
#include "IManagers.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
EditDirectoryDialog::EditDirectoryDialog(DirectorySptr directory)
    : Wt::WDialog("Директория") {
  setClosable(true);
  setWidth(600);
  setHeight(600);
  setMovable(false);

  view_ = contents()->addNew<DirectoryView>(directory);

  Wt::WPushButton* submit = footer()->addNew<Wt::WPushButton>("OK");
  submit->addStyleClass("btn btn-success");
  submit->clicked().connect(this, &EditDirectoryDialog::HandleInput);
}

void EditDirectoryDialog::HandleInput() {
  DirectoryModel* model = view_->model().get();
  view_->updateModel(model);

  if (model->validate()) {
    model->UpdateDirectory();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    managers->directory_manager()->update(model->directory());
    directory_updated_.emit(model->directory());

    auto validation_success = std::make_unique<Wt::WTemplate>(
        Wt::WString::tr("validation-success"));
    validation_success->bindString("text", "Директория успешно изменена");
    view_->bindWidget("validation-status", std::move(validation_success));
  } else {
    view_->bindEmpty("validation-status");
  }

  view_->updateView(model);
}

Wt::Signal<DirectorySptr>& EditDirectoryDialog::directory_updated() {
  return directory_updated_;
}
} // namespace dialog
