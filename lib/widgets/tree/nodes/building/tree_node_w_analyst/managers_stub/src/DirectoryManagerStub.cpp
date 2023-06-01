#include "DirectoryManagerStub.hpp"

DirectoryManagerStub::DirectoryManagerStub(std::vector<Directory> directories) :
    directories_(directories) {}

Directory DirectoryManagerStub::get(size_t directory_id) {
    for (auto e = directories_.begin(); e != directories_.end(); e++)
        if (e->id == directory_id)
            return *e;

    return directories_[0];
}
