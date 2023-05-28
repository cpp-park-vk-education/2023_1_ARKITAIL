#include "CreateDirectoryDialog.hpp"

#include <memory>
#include <string>
#include <vector>

#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>

#include "DirectoryView.hpp"
#include "IManagers.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
CreateDirectoryDialog::CreateDirectoryDialog(ITreeNode* node)
    : Wt::WDialog("Директория"),
      node_(node) {
  setClosable(true);
  setWidth(600);
  setHeight(600);
  setMovable(false);

  view_ = contents()->addNew<DirectoryView>();

  Wt::WPushButton* submit = footer()->addNew<Wt::WPushButton>("OK");
  submit->addStyleClass("btn btn-success");
  submit->clicked().connect(this, &CreateDirectoryDialog::HandleInput);
}

void CreateDirectoryDialog::HandleInput() {
  DirectoryModel* model = view_->model().get();
  view_->updateModel(model);

  if (model->validate()) {
    model->UpdateDirectory();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    size_t directory_id = managers->directory_manager()->add(
        model->directory(),
        node_->getNode().resource_id);
    DirectorySptr created_directory
        = managers->directory_manager()->get(directory_id);
    node_created_.emit(
        managers->node_manager()->get(created_directory->node_id));

    model->reset();
    model->set_directory(nullptr);

    auto validation_success = std::make_unique<Wt::WTemplate>(
        Wt::WString::tr("validation-success"));
    validation_success->bindString("text", "Директория успешно создана");
    view_->bindWidget("validation-status", std::move(validation_success));
  } else {
    view_->bindEmpty("validation-status");
  }

  view_->updateView(model);
}

Wt::Signal<NodeSptr>& CreateDirectoryDialog::node_created() {
  return node_created_;
}
} // namespace dialog
