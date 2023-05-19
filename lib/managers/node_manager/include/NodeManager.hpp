#pragma once

#include <vector>

#include "UnmetDeps.hpp"
#include "INodeManager.hpp"
#include "Node.hpp"
#include "Tag.hpp"

class NodeManager : public INodeManager {
public:
	const Node& get(size_t node_id) override;
	size_t add(const Node& node) override;
	void update(const Node& node) override;
	void remove(size_t node_id) override;

	void tag(const Tag& tag, size_t node_id) override;
	void move(size_t node_id, size_t destination_id) override;
	void subscribe(size_t node_id) override;
	void unsubscribe(size_t node_id) override;
	std::vector<Node> getChildren(size_t node_id) override;

};

