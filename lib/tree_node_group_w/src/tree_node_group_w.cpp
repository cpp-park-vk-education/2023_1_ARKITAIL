#include "tree_node_group_w.hpp"

#include "Wt/WInPlaceEdit.h"
#include "Wt/WLineEdit.h"

TreeNodeGroupW::TreeNodeGroupW(std::string label) {
    title_ = Wt::WString(label);
    label_ = node_block_->addWidget(std::make_unique<Wt::WInPlaceEdit>(false, label));
    label_->setPlaceholderText("Название");
    label_->lineEdit()->setMaxLength(15);
    label_->valueChanged().connect(this, &TreeNodeGroupW::setTitle);
}

void TreeNodeGroupW::setTitle() {
    if (label_->text() != Wt::WString("") && label_->text() != title_) {
        title_ = label_->text();
        // отправить что-то Сене
        std::cout << title_.toUTF8() << std::endl;
    } else {
        label_->setText(title_);
    }
}

Wt::WInteractWidget* TreeNodeGroupW::getTitle() { return label_->textWidget(); }
