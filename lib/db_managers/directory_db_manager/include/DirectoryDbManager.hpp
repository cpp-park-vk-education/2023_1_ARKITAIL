#pragma once

#include <Wt/Dbo/Session.h>

#include "IDirectoryDbManager.hpp"
#include "DbModels.hpp"

class DirectoryDbManager: public IDirectoryDbManager {
public:
  DirectoryDbManager(Wt::Dbo::Session &session) : session_(session) {}

  int add(DirectorySptr) override;
  void remove(int directory_id) override;
  void update(DirectorySptr) override;
  DirectorySptr get(int directory_id) override;

private:
  int id_;
  Wt::Dbo::Session &session_;
};
