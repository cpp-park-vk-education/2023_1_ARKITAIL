#pragma once

#include <memory>

#include "DbMock.hpp"
#include "Directory.hpp"
#include "IDirectoryDbManager.hpp"

class DirectoryDbManagerMock : public IDirectoryDbManager {
public:
    DirectoryDbManagerMock(std::shared_ptr<DbMock> db) ;
    
    const Directory& get(int directory_id);
    int add(const Directory& directory);
    void update(const Directory& directory);
    void remove(int directory_id);

private:
    std::shared_ptr<DbMock> db_;
    int aid_;

};

