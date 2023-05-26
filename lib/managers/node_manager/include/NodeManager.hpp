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

<<<<<<< HEAD
	Node get(size_t node_id) override;
	size_t add(const Node& node) override;
	void update(const Node& node) override;

	void remove(size_t node_id) override;
=======
	const Node& get(int node_id) override;
	int add(const Node& node) override;
	void update(const Node& node) override;

	// Рекурсивное удаление ноды и связанных с ней ресурсов
	void remove(int node_id) override;
>>>>>>> origin/impl-lukyanov

	void tag(const Tag& tag, int node_id) override;
	void move(int node_id, int destination_id) override;
	void subscribe(int node_id) override;
	void unsubscribe(int node_id) override;
	std::vector<Node> getChildren(int node_id) override;

	bool subscribed(size_t node_id) override;

private:
	bool checkAccess(size_t user_id, size_t node_id);

	std::shared_ptr<IDbManagers> db_;

};

