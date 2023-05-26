#pragma once

#include "IDirectoryDbManager.hpp"
#include "mainModel.hpp"

class DirectoryDbManager: public IDirectoryDbManager {
public:
  DirectoryDbManager(dbo::Session &session) : session_(session) {}


  int add(const Directory&);
  void remove(int directory_id);
  void update(const Directory&);
  const Directory& get(int directory_id);

private:
  int id_;
  dbo::Session &session_;
};