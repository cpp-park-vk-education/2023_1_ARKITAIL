#include "tree_node_other_dir_w.hpp"

#include <memory>

#include "Managers.hpp"
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "options_w.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_w.hpp"

TreeNodeOtherDirW::TreeNodeOtherDirW(ITreeNode* node) :
    TreeNodeDirW(node) {}

std::unique_ptr<TreeNodeW> TreeNodeOtherDirW::makeTreeNodeWidget(ITreeNode* node) {
    std::unique_ptr<TreeNodeW> res;
    NodeType node_type = node->getNode().type;
    std::vector<std::string> tags;
    tags.push_back("tag1");
    tags.push_back("tag2");
    if (node_type & NodeType::PUBLIC_CALENDAR) {
        Calendar child = Managers::instance().calendar_manager->get(node->getNode().resource_id);
        res = std::make_unique<TreeNodeLeafW>(node);
        auto options = std::make_unique<OptionsW>();
        options->addOptionSubscribe();  //Нужна проверка на подписку
        options->addOptionUnsubscribe();
        res.get()
            ->addOptions(std::move(options))
            ->addToolTip(child.description, tags,
                         Managers::instance().user_manager->get(child.owner_id));

    } else if (node_type & NodeType::PUBLIC_DIRECTORY) {
        Directory child = Managers::instance().directory_manager->get(node->getNode().resource_id);
        res = std::make_unique<TreeNodeDirW>(node);
        res.get()->addToolTip(child.description, tags,
                              Managers::instance().user_manager->get(child.owner_id));
    }
    res.get()->endNode()->addParent(this);
    return res;
}
