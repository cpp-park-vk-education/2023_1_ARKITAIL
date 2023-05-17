#include "tree_node_profile_w.hpp"

#include "Wt/WInPlaceEdit.h"
#include "Wt/WLineEdit.h"

TreeNodeProfileW::TreeNodeProfileW(std::string label, ITreeNode* node) : TreeNodeLeafW(node) {
    title_ = Wt::WString(label);
    label_ = node_block_->addWidget(std::make_unique<Wt::WInPlaceEdit>(false, label));
    label_->setPlaceholderText("Название");
    label_->lineEdit()->setMaxLength(15);
    label_->valueChanged().connect(this, &TreeNodeProfileW::setTitle);
}

void TreeNodeProfileW::setTitle() {
    if (label_->text() != Wt::WString("") && label_->text() != title_) {
        title_ = label_->text();
        // отправить что-то Сене
        std::cout << title_.toUTF8() << std::endl;
    } else {
        label_->setText(title_);
    }
}

Wt::WInteractWidget* TreeNodeProfileW::getTitle() { return label_->textWidget(); }
