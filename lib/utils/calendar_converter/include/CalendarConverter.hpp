#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <Wt/WDateTime.h>
#include <Wt/WDate.h>
#include <Wt/WString.h>

#include "ICharacterReader.hpp"
#include "IStreamBuffer.hpp"

#include "Event.hpp"
#include "Calendar.hpp"
#include "Parser.hpp"

class CalendarConverter {
 public:
   // метод принимает ICharacterReader, из которого лексер будет получать
   // символы, и возвращает вектор id'шников сохранённых календарей
   static std::vector<size_t> IcalendarToCalendars(
       std::unique_ptr<parsing::ICharacterReader>&& reader);

   // метод принимает вектор id'шников календарей, по которым будет получать
   // эти календари у CalendarManager
  static std::stringstream CalendarToIcalendar(CalendarSptr calendar);
 private:
  static EventSptr FromIcalendarEvent(const parsing::ComponentUptr& icalendar_event);
  static Wt::WDateTime FromIcalendarDateTime(const std::string& icalendar_date_time);
  static Wt::WDate FromIcalendarDate(const std::string& icalendar_date);
  
  static void Write(
    std::stringstream& ss,
    const Wt::WString& name,
    const Wt::WString& value);

  static Wt::WString FromCalendarDateTime(const Wt::WDateTime& date_time);
  static Wt::WString FromCalendarRrule(const EventSptr event);
  static Wt::WString FromCalendarDate(const Wt::WDate& date);
};
