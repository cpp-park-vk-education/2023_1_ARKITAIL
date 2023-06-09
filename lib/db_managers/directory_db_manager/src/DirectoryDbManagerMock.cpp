#include "DirectoryDbManagerMock.hpp"
#include "DbMock.hpp"
#include "Directory.hpp"

DirectoryDbManagerMock::DirectoryDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db),
	aid_(db_->directories.size()) {}

DirectorySptr DirectoryDbManagerMock::get(int directory_id) {
	for (auto e = db_->directories.begin(); e != db_->directories.end(); e++) 
		if (e->id == directory_id)
			return std::make_shared<Directory>(*e);

	return std::make_shared<Directory>(db_->directories[0]);
}

int DirectoryDbManagerMock::add(DirectorySptr directory) {
	db_->directories.emplace_back(
		aid_,
		directory->node_id,
		directory->owner_id,
		directory->name,
		directory->description
	);

	return aid_++;
}

void DirectoryDbManagerMock::update(DirectorySptr directory) {
	for (auto e : db_->directories)
		if (e.id == directory->id)
			e = *directory;
}

void DirectoryDbManagerMock::remove(int directory_id) {
	for (auto e = db_->directories.begin() + 1; e != db_->directories.end(); e++)
		if (e->id == directory_id)
			db_->directories.erase(e);
}

