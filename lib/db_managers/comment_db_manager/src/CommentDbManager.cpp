#include "CommentDbManager.hpp"

#include <memory>

#include <Wt/Dbo/Transaction.h>

#include "DbModels.hpp"
#include "Session.hpp"

CommentDbManager::CommentDbManager(Session& session)
    : session_(session) {
}

int CommentDbManager::add(CommentSptr) {
  // TODO
  
  return -1;
}

void CommentDbManager::remove(int) {
  // TODO
}

void CommentDbManager::update(CommentSptr) {
  // TODO
}

CommentSptr CommentDbManager::get(int) {
  // TODO
  
  return std::shared_ptr<Comment>();
}
