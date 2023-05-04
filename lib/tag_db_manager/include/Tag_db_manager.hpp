#pragma once

#include "Tag_db_model.hpp"

class tag_manager {
public:
    tags addTag(tags);
    tags deleteTag(int id);
    tags upgradeTag(tags);
    tags getTag(int id);
};