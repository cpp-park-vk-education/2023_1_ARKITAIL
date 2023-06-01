#pragma once

#include "IDirectoryDbManager.hpp"
#include "DbModels.hpp"
#include "Session.hpp"

class DirectoryDbManager: public IDirectoryDbManager {
public:
  DirectoryDbManager() = delete;
  explicit DirectoryDbManager(Session& session);

  int add(DirectorySptr directory) override;
  void remove(int directory_id) override;
  void update(DirectorySptr directory) override;
  DirectorySptr get(int directory_id) override;

private:
  Session& session_;

};

