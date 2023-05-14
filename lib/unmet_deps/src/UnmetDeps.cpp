#include <vector>

#include "UnmetDeps.hpp"
#include "Directory.hpp"
#include "Node.hpp"

const Directory& DirectoryDbManager::get(size_t) {
	return *(new Directory());  // dummy
}

size_t DirectoryDbManager::add(const Directory&) {
	return 0;
}

size_t DirectoryDbManager::update(const Directory&) {
	return 0;
}

void DirectoryDbManager::remove(size_t) {}

std::vector<Directory> DirectoryDbManager::getChildren(size_t){
	return std::vector<Directory>();
}

const Node& NodeDbManager::get(size_t node_id) {
	return *(new Node());
}

size_t NodeDbManager::add(const Node& node) {
	return 0;
}

size_t NodeDbManager::update(const Node& node) {
	return 0;
}

void NodeDbManager::remove(size_t node_id) {}

std::vector<Node> NodeDbManager::getChildren(size_t node_id) {
	return std::vector<Node>();
}

