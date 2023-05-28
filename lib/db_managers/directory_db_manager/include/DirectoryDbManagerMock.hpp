#pragma once

#include <memory>

#include "DbMock.hpp"
#include "Directory.hpp"
#include "IDirectoryDbManager.hpp"

class DirectoryDbManagerMock : public IDirectoryDbManager {
public:
    DirectoryDbManagerMock(std::shared_ptr<DbMock> db) ;
    
    DirectorySptr get(int directory_id) override;
    int add(DirectorySptr directory) override;
    void update(DirectorySptr directory) override;
    void remove(int directory_id) override;

private:
    std::shared_ptr<DbMock> db_;
    int aid_;

};

