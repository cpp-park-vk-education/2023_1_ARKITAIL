#pragma once

#include "DbModels.hpp"
#include "ITagDbManager.hpp"

class TagDbManager: public ITagDbManager {
public:
  TagDbManager(Wt::Dbo::Session &session) : session_(session) {}

  int add(TagSptr tag) override;
  void remove(int tag_id) override;
	void update(TagSptr tag) override;
  TagSptr get(int tag_id) override;

private:
  int id_;
  Wt::Dbo::Session &session_;
};
