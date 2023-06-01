#include "TagsLineEdit.hpp"

#include "Tag.hpp"

TagsLineEdit::TagsLineEdit() {}

void TagsLineEdit::appendItem(const Tag& tag) {
    std::cout << "\nпоиск какого-то тега " << tag.name << "\n\n";
}
