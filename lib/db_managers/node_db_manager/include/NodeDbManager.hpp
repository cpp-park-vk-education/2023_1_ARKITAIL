#pragma once

#include <Wt/Dbo/Session.h>

#include "DbModels.hpp"
#include "INodeDbManager.hpp"
#include "Node.hpp"
#include "Tag.hpp"

class NodeDbManager: public INodeDbManager {
public:
  NodeDbManager(Wt::Dbo::Session &session) : session_(session) {}

  int add(NodeSptr node) override;
  void remove(int node_id) override;
  void update(NodeSptr node) override;
  NodeSptr get(int node_id) override;

  std::vector<Node> getChildren(int node_id) override;
  
  void tag(int node_id, TagSptr tag) override;
  void move(int node_id, int destination_id) override;

private:
  int id_;
  int destination_id_;
  Wt::Dbo::Session &session_;
};
