#include "StringStreamResource.hpp"

#include <istream>

#include <Wt/WStreamResource.h>

#include "IStreamBuffer.hpp"

StringStreamResource::StringStreamResource(
    std::unique_ptr<parsing::IStreamBuffer>&& buffer)
    : Wt::WStreamResource("text/calendar"),
      is_(buffer->Buffer()) {
  suggestFileName("calendar.ics");
}

StringStreamResource::~StringStreamResource() {
  beingDeleted();
}

void StringStreamResource::handleRequest(
    const Wt::Http::Request &request,
    Wt::Http::Response &response) {
  handleRequestPiecewise(request, response, is_);
}
