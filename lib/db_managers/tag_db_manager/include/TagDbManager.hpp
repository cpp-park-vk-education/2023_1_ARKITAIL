#pragma once

#include "DbModels.hpp"
#include "ITagDbManager.hpp"
#include "Session.hpp"

class TagDbManager: public ITagDbManager {
public:
  TagDbManager() = delete;
  explicit TagDbManager(Session &session);

  int add(TagSptr tag) override;
  void remove(int tag_id) override;
	void update(TagSptr tag) override;
  TagSptr get(int tag_id) override;
  
	std::vector<Node> NodeByTag(int tag) override {}

private:
  Session& session_;

};

