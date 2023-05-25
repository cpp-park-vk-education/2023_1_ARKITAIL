#pragma once

#include "mainModel.hpp"
#include "INodeDbManager.hpp"


class NodeDbManager: public INodeDbManager {
public:
  NodeDbManager(dbo::Session &session) : session_(session) {}

  int add(const Node &);
  void remove(int node_id);
  void update(const Node &);
  const Node& get(int node_id);

  std::vector<Node> getChildren(int node_id);

private:
  int id_;
  dbo::Session &session_;
};