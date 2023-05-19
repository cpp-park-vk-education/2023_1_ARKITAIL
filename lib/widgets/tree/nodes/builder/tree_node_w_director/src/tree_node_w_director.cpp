#include "tree_node_w_director.hpp"

#include <Wt/WAnchor.h>
#include <Wt/WBreak.h>

#include "ITreeNode.hpp"
#include "Node.hpp"
#include "tree_node_w_builder.hpp"

TreeNodeWDirector::TreeNodeWDirector() {}

std::unique_ptr<TreeNodeW> TreeNodeWDirector::createNode(TreeNodeWType type, ITreeNode* this_node,
                                                         TreeNodeW* parent_node) {}
