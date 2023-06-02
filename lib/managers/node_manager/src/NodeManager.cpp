#include "NodeManager.hpp"

#include <Wt/WLogger.h>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "Calendar.hpp"
#include "DbManagers.hpp"
#include "Directory.hpp"
#include "IDbManagers.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "Tag.hpp"
#include "User.hpp"

NodeManager::NodeManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

bool NodeManager::checkAccess(int user_id, int node_id) {
    NodeSptr node = db_->node_dbm()->get(node_id);

    if (node->type & DIRECTORY)
        return db_->directory_dbm()->get(node->resource_id)->owner_id == user_id;

    if (node->type & CALENDAR)
        return db_->calendar_dbm()->get(node->resource_id)->owner_id == user_id;

    if (node->type & MOUNT)
        return checkAccess(user_id, node->parent_id);

    return false;
}

NodeSptr NodeManager::get(int node_id) {
    UserSptr user = db_->user_dbm()->get();

    // if (!checkAccess(user->id, node_id))
    // 	return nullptr;

    NodeSptr node = db_->node_dbm()->get(node_id);

    return node;
}

// В ноду типа PRIVATE_{GROUP | DIRECTORY}
// можно добавить только PRIVATE_{DIRECTORY | CALENDAR}
// Аналогично и для PUBLIC
// В ноду типа SUBSCRIPTIONS_GROUP
// можно добавить только MOUNT и наоборот
// В ноды ROOT, MOUNT, PUBLIC_CALENDAR, PRIVATE_CALENDAR добавить ничего нельзя
// Ресурсом MOUNT может быть только нодой с ресурсом PUBLIC_{DIRECTORY | CALENDAR}
int NodeManager::add(NodeSptr node) {

    UserSptr user = db_->user_dbm()->get();

    if (!checkAccess(user->id, node->parent_id)) {
        return 0;
    }

    if (node->type & DIRECTORY) {
        NodeSptr parent_node = db_->node_dbm()->get(node->parent_id);

        if (!(parent_node->type & PRIVATE_GD && node->type & PRIVATE_DIRECTORY ||
              parent_node->type & PUBLIC_GD && node->type & PUBLIC_DIRECTORY ||
              checkAccess(user->id, node->id))) {

            return 0;
        }


    } else if (node->type & CALENDAR) {
        NodeSptr parent_node = db_->node_dbm()->get(node->parent_id);

        if (!(parent_node->type & PRIVATE_GD && node->type & PRIVATE_CALENDAR ||
              parent_node->type & PUBLIC_GD && node->type & PUBLIC_CALENDAR ||
              checkAccess(user->id, node->id))) {
            
            return 0;
        }

    } else if (node->type & MOUNT) {

        NodeSptr parent_node = db_->node_dbm()->get(node->parent_id);

        if (!(parent_node->type & SUBSCRIPTIONS_GROUP)) {
            return 0;
        }

        NodeSptr resource_node = db_->node_dbm()->get(node->resource_id);

        if (!(resource_node->type & (PUBLIC_DIRECTORY | PUBLIC_CALENDAR))) {
            return 0;
        }
    } else if (node->type & PROFILE) {
        // write some validation
    } else {
        return 0;
    }

    NodeSptr new_node = node;
    new_node->id = db_->node_dbm()->add(node);

    return new_node->id;
}

// Можно менять только поле parent_id функция аналогична NodeManager::move
void NodeManager::update(NodeSptr node) {
    UserSptr user = db_->user_dbm()->get();
    NodeSptr prev_node = db_->node_dbm()->get(node->id);
    NodeSptr prev_parent_node = db_->node_dbm()->get(prev_node->parent_id);
    NodeSptr parent_node = db_->node_dbm()->get(node->parent_id);
    if (!checkAccess(user->id, parent_node->id) ||
        prev_parent_node->type != parent_node->type ||
        prev_node->type != node->type)
        return;
    db_->node_dbm()->update(node);
}

// Удалять запрещено типы ROOT, {PRIVATE | PUBLIC | SUBSCRIPTIONS | PROFILE}_GROUP
void NodeManager::remove(int node_id) {
    UserSptr user = db_->user_dbm()->get();
    NodeSptr node = db_->node_dbm()->get(node_id);

    if (!checkAccess(user->id, node->id) ||
        node->type & (ROOT | PRIVATE_GROUP | PUBLIC_GROUP | SUBSCRIPTIONS_GROUP | PROFILE_GROUP))
        return;

    std::queue<NodeSptr> subtree;
    subtree.push(node);

    NodeSptr cur_node = nullptr;

    while (!subtree.empty()) {
        cur_node = subtree.front();

        if (cur_node->type & (PRIVATE_DIRECTORY | PUBLIC_DIRECTORY))
            for (auto child_node : db_->node_dbm()->getChildren(cur_node->id))
                subtree.push(std::make_shared<Node>(child_node));

        db_->node_dbm()->remove(cur_node->id);

        if (cur_node->type & (PRIVATE_DIRECTORY | PUBLIC_DIRECTORY))
            db_->directory_dbm()->remove(cur_node->resource_id);
        else if (cur_node->type & (PRIVATE_CALENDAR | PUBLIC_CALENDAR))
            db_->calendar_dbm()->remove(cur_node->resource_id);

        subtree.pop();
    }
}

void NodeManager::tag(TagSptr tag, int node_id) {
	// TODO(uma_op): IMPLEMENT ME
}

// Проверка на то, что перемещение осуществляется только внутри дерева одного пользователя
// и в ноды с валидными типами
void NodeManager::move(int node_id, int destination_id) {
    NodeSptr mvd_node = db_->node_dbm()->get(node_id);
    mvd_node->parent_id = destination_id;
    update(mvd_node);
}

// TODO(uma_op): Проверка на права доступа
// Подписка может осуществиться только на PUBLIC_{DIRECTORY | CALENDAR}
void NodeManager::subscribe(int node_id) {
    UserSptr user = db_->user_dbm()->get();
    NodeSptr node = db_->node_dbm()->get(node_id);

    if (!(node->type & (PUBLIC_DIRECTORY | PUBLIC_CALENDAR)))
        return;

    for (Node subg : db_->node_dbm()->getChildren(user->root_id)) {
        if (subg.type & SUBSCRIPTIONS_GROUP) {
            // affeeal: возможно, ошибка: точно не знаю, чей owner_id ставить
            NodeSptr mount_node = std::make_shared<Node>(
                0, subg.id, node_id, subg.owner_id, MOUNT);
            add(mount_node);
            break;
        }
    }
}

// Отписка является одной из самых безобидных операций
// и не требует никаких проверок
void NodeManager::unsubscribe(int node_id) {
    UserSptr user = db_->user_dbm()->get();

    for (auto subg : db_->node_dbm()->getChildren(user->root_id))
        if (subg.type & SUBSCRIPTIONS_GROUP) {
            for (auto sub : db_->node_dbm()->getChildren(subg.id)) {
                if (sub.resource_id == node_id) {
                    db_->node_dbm()->remove(sub.id);
                    break;
                }
            }
            break;
        }
}

// Получение детей так же как и получение требует лишь проверки прав доступа
std::vector<Node> NodeManager::getChildren(int node_id) {
    UserSptr user = db_->user_dbm()->get();
    NodeSptr node = db_->node_dbm()->get(node_id);

    if (!(checkAccess(user->id, node_id) || node->type & PUBLIC))
        return std::vector<Node>();

    return db_->node_dbm()->getChildren(node_id);
}

bool NodeManager::subscribed(int node_id) {
    UserSptr user = db_->user_dbm()->get();
    NodeSptr root = db_->node_dbm()->get(user->root_id);

    for (auto c : db_->node_dbm()->getChildren(root->id))
	    if (c.type & SUBSCRIPTIONS_GROUP)
	        for (auto s : db_->node_dbm()->getChildren(c.id))
	    	    if (s.resource_id == node_id)
	    	        return true;


    return false;
}
