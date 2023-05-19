#include "DirectoryDbManagerMock.hpp"
#include "Directory.hpp"

DirectoryDbManagerMock::DirectoryDbManagerMock() :
	data_(),
	aid_(1) {
	
	data_.emplace_back(0, 0, 0, "", "");
}

const Directory& DirectoryDbManagerMock::get(size_t directory_id) {
	for (auto e = data_.begin(); e != data_.end(); e++) 
		if (e->id == directory_id)
			return *e;

	return data_[0];
}

size_t DirectoryDbManagerMock::add(const Directory& directory) {
	data_.emplace_back(
		aid_,
		directory.node_id,
		directory.owner_id,
		directory.name,
		directory.description
	);

	return aid_++;
}

void DirectoryDbManagerMock::update(const Directory& directory) {
	for (auto e : data_)
		if (e.id == directory.id)
			e = directory;
}

void DirectoryDbManagerMock::remove(size_t directory_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == directory_id)
			data_.erase(e);
}

