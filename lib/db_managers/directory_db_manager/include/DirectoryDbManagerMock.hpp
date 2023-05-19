#pragma once

#include "Directory.hpp"
#include "IDirectoryDbManager.hpp"

class DirectoryDbManagerMock : public IDirectoryDbManager {
public:
    DirectoryDbManagerMock();
    
    const Directory& get(size_t directory_id);
    size_t add(const Directory& directory);
    void update(const Directory& directory);
    void remove(size_t directory_id);

private:
    std::vector<Directory> data_;
    size_t aid_;

};

