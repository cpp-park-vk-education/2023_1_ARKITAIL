#pragma once

#include <memory>
#include <vector>

#include "IDbManagers.hpp"
#include "INodeManager.hpp"
#include "Node.hpp"
#include "Tag.hpp"

// Проверки доступа
class NodeManager : public INodeManager {
public:
	NodeManager(std::shared_ptr<IDbManagers> db);

	Node get(size_t node_id) override;
	size_t add(const Node& node) override;
	void update(const Node& node) override;

	// Рекурсивное удаление ноды и связанных с ней ресурсов
	void remove(size_t node_id) override;

	void tag(const Tag& tag, size_t node_id) override;
	void move(size_t node_id, size_t destination_id) override;
	void subscribe(size_t node_id) override;
	void unsubscribe(size_t node_id) override;
	std::vector<Node> getChildren(size_t node_id) override;

private:
	bool checkOwnership(size_t user_id, size_t node_id);

	std::shared_ptr<IDbManagers> db_;

};

