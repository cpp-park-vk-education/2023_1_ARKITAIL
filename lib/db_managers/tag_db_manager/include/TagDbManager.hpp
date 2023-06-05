#pragma once

#include "DbModels.hpp"
#include "ITagDbManager.hpp"
#include "Session.hpp"
#include "Tag.hpp"
#include <string>

class TagDbManager: public ITagDbManager {
public:
  TagDbManager() = delete;
  explicit TagDbManager(Session &session);

  TagSptr get(int tag_id) override;
  int add(TagSptr tag) override;
  void remove(int tag_id) override;
  void update(TagSptr tag) override;
  
  TagSptr find(const std::string& tag_name) override;
  std::vector<Node> NodeByTag(int tag) override;

private:
  Session& session_;

};

