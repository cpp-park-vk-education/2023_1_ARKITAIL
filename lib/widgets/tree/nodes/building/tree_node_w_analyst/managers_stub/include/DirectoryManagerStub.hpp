#pragma once

#include <vector>

#include "Directory.hpp"
#include "IDirectoryManager.hpp"
#include "Node.hpp"

class DirectoryManagerStub : public IDirectoryManager {
  public:
    DirectoryManagerStub(std::vector<Directory> directories);
    DirectorySptr get(int directory_id) override;

  private:
    int add(DirectorySptr directory, int directory_id) override {
        return 0;
    }

    void update(DirectorySptr directory) override {}

    void remove(int directory_id) override {}

    std::vector<Event> getEvents(int directory_id) override {
        return std::vector<Event>();
    }

    std::vector<Directory> directories_;
};
