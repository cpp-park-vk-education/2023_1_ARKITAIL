#pragma once

#include <memory>
#include <vector>

#include "DbMock.hpp"
#include "INodeDbManager.hpp"

class NodeDbManagerMock : public INodeDbManager {
public:
  NodeDbManagerMock(std::shared_ptr<DbMock> db);

  NodeSptr get(int node_id) override;
  int add(NodeSptr node) override;
  void update(NodeSptr node) override;
  void remove(int node_id) override;

  std::vector<Node> getChildren(int node_id) override;
  void profile(int node_id, ProfileSptr profile) override;
  void tag(int node_id, TagSptr tag) override;
  void move(int node_id, int destination_id) override;

private:
  std::shared_ptr<DbMock> db_;
  int aid_;
};
