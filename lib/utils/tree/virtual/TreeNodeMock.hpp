#include "ITreeNode.hpp"

class TreeNodeMock : public ITreeNode {
public:
    TreeNodeMock(Node node, ITreeNode* parent);

    Node getNode();
    ITreeNode* getParent();

    std::vector<ITreeNode*> getChildren();
    ITreeNode* addChild(Node node);
    std::unique_ptr<ITreeNode> remove();

    bool isChecked();

    void check();
    void uncheck();
    
private:
    std::unique_ptr<ITreeNode> removeChild(ITreeNode* child);

    Node node_;
    ITreeNode* parent_;
    std::vector<std::unique_ptr<ITreeNode>> children_;
    bool checked_;

};

