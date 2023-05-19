#include "DirectoryDbManagerMock.hpp"
#include "Directory.hpp"

DirectoryDbManagerMock::DirectoryDbManagerMock() :
	data_(),
	aid_() {
	
	data_.emplace_back(0, 0, 0, "", "");

	data_.emplace_back(1, 1, 0, "UmaOpRoot", "desc");
	data_.emplace_back(2, 2, 1, "TestRoot", "desc");
	data_.emplace_back(3, 3, 0, "UmaOpPrivate", "desc");
	data_.emplace_back(4, 4, 0, "UmaOpPublic", "desc");
	data_.emplace_back(5, 5, 0, "UmaOpSubscriptions", "desc");
	data_.emplace_back(6, 6, 0, "UmaOpProfile", "desc");
	data_.emplace_back(7, 7, 0, "PrivateDirecotry", "desc");
	data_.emplace_back(8, 10, 0, "PublicDirectory", "desc");
	data_.emplace_back(9, 15, 1, "TestPrivate", "desc");
	data_.emplace_back(10, 16, 1, "TestPublic", "desc");
	data_.emplace_back(11, 17, 1, "TestSubscriptions", "desc");
	data_.emplace_back(12, 18, 1, "TestProfile", "desc");
	data_.emplace_back(13, 19, 1, "PrivateDirectory", "desc");
	data_.emplace_back(14, 22, 1, "PublicDirectory", "desc");

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

