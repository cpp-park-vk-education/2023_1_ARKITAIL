#pragma once

#include <memory>
#include <vector>

#include "IDbManagers.hpp"
#include "INodeManager.hpp"
#include "Node.hpp"
#include "Tag.hpp"

class NodeManager : public INodeManager {
public:
	NodeManager(std::shared_ptr<IDbManagers> db);

	NodeSptr get(int node_id) override;
	int add(NodeSptr node) override;
	void update(NodeSptr node) override;

	void remove(int node_id) override;

	void tag(TagSptr tag, int node_id) override;
	void move(int node_id, int destination_id) override;
	void subscribe(int node_id) override;
	void unsubscribe(int node_id) override;
	std::vector<Node> getChildren(int node_id) override;

	bool subscribed(int node_id) override;

private:
	bool checkAccess(int user_id, int node_id);

	std::shared_ptr<IDbManagers> db_;

};

