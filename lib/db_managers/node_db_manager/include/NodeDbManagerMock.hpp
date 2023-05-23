#pragma once

#include <memory>
#include <vector>

#include "DbMock.hpp"
#include "INodeDbManager.hpp"

class NodeDbManagerMock: public INodeDbManager{
public:
  NodeDbManagerMock(std::shared_ptr<DbMock> db);

  const Node &get(int node_id);
  int add(const Node &node);
  void update(const Node &node);
  void remove(int node_id);

//   void tag(int node_id, const Tag &);
//   void move(int node_id, int destination_id);
  std::vector<Node> getChildren(int node_id);

private:
  std::shared_ptr<DbMock> db_;
  int aid_;
};
