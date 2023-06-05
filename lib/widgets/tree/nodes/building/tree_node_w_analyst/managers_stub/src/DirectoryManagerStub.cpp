#include "DirectoryManagerStub.hpp"

DirectoryManagerStub::DirectoryManagerStub(std::vector<Directory> directories) :
    directories_(directories) {}

DirectorySptr DirectoryManagerStub::get(int directory_id) {
    for (auto e = directories_.begin(); e != directories_.end(); e++)
        if (e->id == directory_id)
            return std::make_shared<Directory>(*e);

    return std::make_shared<Directory>(directories_[0]);
}
