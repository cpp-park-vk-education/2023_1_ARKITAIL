#pragma once

#include "DbModels.hpp"
#include "INodeDbManager.hpp"
#include "Node.hpp"
#include "Session.hpp"
#include "Tag.hpp"

class NodeDbManager: public INodeDbManager {
public:
  NodeDbManager() = delete;
  explicit NodeDbManager(Session& session);

  int add(NodeSptr node) override;
  void remove(int node_id) override;
  void update(NodeSptr node) override;
  NodeSptr get(int node_id) override;

  std::vector<Node> getChildren(int node_id) override;
  void tag(int node_id, int tag_id) override;
  std::vector<TagSptr> tagByNode(int node_id) override;

private:
  Session& session_;

};

