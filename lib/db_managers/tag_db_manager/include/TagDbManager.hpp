#pragma once

#include "mainModel.hpp"
#include "ITagDbManager.hpp"

class TagDbManager: public ITagDbManager {
public:
  TagDbManager(dbo::Session &session) : session_(session) {}

  int add(const Tag &);
  void remove(int tag_id);
  const Tag& get(int tag_id);

private:
  int id_;
  dbo::Session &session_;
};