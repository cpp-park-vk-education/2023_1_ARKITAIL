#pragma once

#include "DbModels.hpp"
#include "ITagDbManager.hpp"
#include "Node.hpp"
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
  
  TagSptr find(const std::string& tag_name) override;
  std::vector<NodeSptr> nodeByTag(int tag) override;

private:
  Session& session_;

};

