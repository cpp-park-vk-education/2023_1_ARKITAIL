#pragma once

#include <memory>

#include <Wt/WResource.h>
#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>

#include "i_char_reader.hpp"

class StringStreamResource : public Wt::WResource {
 public:
  StringStreamResource(std::unique_ptr<ICharReader>&& char_reader);
  ~StringStreamResource();

  void handleRequest(
      const Wt::Http::Request& request,
      Wt::Http::Response& response) override;
 private:
  std::unique_ptr<ICharReader> char_reader_;
};
