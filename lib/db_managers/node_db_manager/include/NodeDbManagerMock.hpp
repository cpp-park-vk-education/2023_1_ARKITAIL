#pragma once

#include <memory>
#include <vector>

#include "DbMock.hpp"
#include "INodeDbManager.hpp"
#include "Tag.hpp"

class NodeDbManagerMock: public INodeDbManager{
public:
  NodeDbManagerMock(std::shared_ptr<DbMock> db);

  NodeSptr get(int node_id) override;
  int add(NodeSptr node) override;
  void update(NodeSptr node) override;
  void remove(int node_id) override;

  std::vector<Node> getChildren(int node_id) override;
  void tag(int node_id, int tag_id) override;
  std::vector<TagSptr> tagByNode(int node_id) override;

private:
  std::shared_ptr<DbMock> db_;
  int aid_;

};

