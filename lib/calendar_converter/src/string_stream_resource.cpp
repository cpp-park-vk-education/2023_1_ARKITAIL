#include "string_stream_resource.hpp"

#include <iostream>
#include <sstream>

#include <Wt/WStreamResource.h>

StringStreamResource::StringStreamResource(std::stringstream&& ss)
  : Wt::WStreamResource(),
    ss_(std::move(ss)) {
  suggestFileName("calendar.ics");
}

StringStreamResource::~StringStreamResource() {
  beingDeleted();
}

void StringStreamResource::handleRequest(
    const Wt::Http::Request &request,
    Wt::Http::Response &response) {
  std::cout << "???" << std::endl;
  handleRequestPiecewise(request, response, ss_);
}
