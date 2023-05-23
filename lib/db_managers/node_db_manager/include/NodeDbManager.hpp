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

  void tag(int node_id, const Tag &);
  void move(int node_id, int destination_id);
  std::vector<Node> getChildren(int node_id);

private:
  int id_;
  int destination_id_;
  dbo::Session &session_;
};