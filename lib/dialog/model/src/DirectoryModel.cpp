#include "DirectoryModel.hpp"

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>
#include <Wt/WLengthValidator.h>

#include "Directory.hpp"

namespace dialog {
const Wt::WFormModel::Field DirectoryModel::kName = "name";
const Wt::WFormModel::Field DirectoryModel::kDescription = "description";

// по умолчанию directory = nullptr
DirectoryModel::DirectoryModel(DirectorySptr directory)
    : Wt::WFormModel(),
      directory_(directory) {
  AddFields();
  SetValidators();
  SetValues();
}

void DirectoryModel::UpdateDirectory() {
  if (!directory_) {
    directory_ = std::make_shared<Directory>();
  }

  directory_->name = Wt::asString(value(kName)).toUTF8();
  directory_->description = Wt::asString(value(kDescription)).toUTF8();
}

DirectorySptr DirectoryModel::directory() const {
  return directory_;
}

void DirectoryModel::set_directory(DirectorySptr directory) {
  directory_ = directory;
}

void DirectoryModel::AddFields() {
  addField(kName);
  addField(kDescription);
}

void DirectoryModel::SetValidators() {
  setValidator(kName, CreateNameValidator());
  validator(kName)->setMandatory(true);
}

void DirectoryModel::SetValues() {
  if (directory_) {
    setValue(kName, directory_->name);
    setValue(kDescription, directory_->description);
  }
}

std::shared_ptr<Wt::WValidator> DirectoryModel::CreateNameValidator() {
  auto validator = std::make_shared<Wt::WLengthValidator>();

  validator->setInvalidBlankText("Пожалуйста, укажите название");
  validator->setMinimumLength(1);
  validator->setMaximumLength(50);

  return validator;
}
} // namespace dialog
