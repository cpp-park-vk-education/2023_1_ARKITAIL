#pragma once

#include <memory>

#include "DbMock.hpp"
#include "Directory.hpp"
#include "IDirectoryDbManager.hpp"

class DirectoryDbManagerMock : public IDirectoryDbManager {
public:
    DirectoryDbManagerMock(std::shared_ptr<DbMock> db) ;
    
    const Directory& get(size_t directory_id);
    size_t add(const Directory& directory);
    void update(const Directory& directory);
    void remove(size_t directory_id);

private:
    std::shared_ptr<DbMock> db_;
    size_t aid_;

};

