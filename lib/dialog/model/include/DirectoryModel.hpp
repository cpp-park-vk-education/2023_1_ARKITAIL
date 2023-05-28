#pragma once

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "Directory.hpp"

namespace dialog {
class DirectoryModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kName;
  static const Wt::WFormModel::Field kDescription;

  explicit DirectoryModel(DirectorySptr directory = nullptr);

  void UpdateDirectory();

  DirectorySptr directory() const;

  void set_directory(DirectorySptr directory);
 private:
  void AddFields();
  void SetValidators();
  void SetValues();

  std::shared_ptr<Wt::WValidator> CreateNameValidator();

  DirectorySptr directory_;
};
} // namespace dialog
