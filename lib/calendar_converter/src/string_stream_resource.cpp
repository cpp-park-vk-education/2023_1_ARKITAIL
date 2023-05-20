#include "string_stream_resource.hpp"

#include <Wt/WResource.h>

#include <sstream>

#include "i_char_reader.hpp"

StringStreamResource::StringStreamResource(
    std::unique_ptr<ICharReader>&& char_reader)
    : Wt::WResource(),
      char_reader_(std::move(char_reader)) {
  suggestFileName("calendar.ics");
}

StringStreamResource::~StringStreamResource() {
  beingDeleted();
}

void StringStreamResource::handleRequest(
    [[maybe_unused]] const Wt::Http::Request &request,
    Wt::Http::Response &response) {
  response.setMimeType("text/calendar");

  // TODO(affeeal): исправить на изъятие
  // буффера у char_reader:
  std::stringstream ss;
  while (!char_reader_->IsEof()) {
    ss << char_reader_->Get();
  }
  response.out() << ss.str();
}
