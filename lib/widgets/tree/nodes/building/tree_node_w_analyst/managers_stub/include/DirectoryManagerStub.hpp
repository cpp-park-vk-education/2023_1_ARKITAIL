#pragma once

#include <vector>

#include "Directory.hpp"
#include "IDirectoryManager.hpp"
#include "Node.hpp"

class DirectoryManagerStub : public IDirectoryManager {
  public:
    DirectoryManagerStub(std::vector<Directory> directories);
    Directory get(size_t directory_id) override;

  private:
    size_t add(const Directory& directory, size_t directory_id) override {
        return size_t();
    }

    void update(const Directory& directory) override {}

    void remove(size_t directory_id) override {}

    std::vector<EventSptr> getEvents(size_t directory_id) override {
        return std::vector<EventSptr>();
    }

    std::vector<Directory> directories_;
};
