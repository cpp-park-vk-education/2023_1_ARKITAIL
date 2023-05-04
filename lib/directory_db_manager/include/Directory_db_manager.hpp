#pragma once

#include "Directory_db_model.hpp"

class directory_manager {
public:
    directory addDirectory(directory);
    directory deleteDirectory(int id);
    directory getDirectory(int id);
};