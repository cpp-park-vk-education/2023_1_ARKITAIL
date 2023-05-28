#pragma once

#include <vector>

#include "Tag.hpp"
#include "Node.hpp"

class INodeManager {
public:
	virtual NodeSptr get(int node_id) = 0;
	virtual int add(NodeSptr node) = 0;
	virtual void update(NodeSptr node) = 0;
	virtual void remove(int node_id) = 0;

	virtual void tag(TagSptr tag, int node_id) = 0;
	virtual void move(int node_id, int destination_id) = 0;
	virtual void subscribe(int node_id) = 0;
	virtual void unsubscribe(int node_id) = 0;
	virtual std::vector<Node> getChildren(int node_id) = 0;

  virtual bool subscribed(int node_id) = 0;
};

