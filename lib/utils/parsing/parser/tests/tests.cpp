#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>
#include <queue>

#include "IstreamCharacterReader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

class IcalendarParserTest : public ::testing::Test {
 protected:
  void SetUp() override {
    lexer_.set_character_reader(reader_);
    parser_.set_lexer(lexer_);
  }

  void TearDown() override {
  }

  parsing::IstreamCharacterReader reader_;
  parsing::IcalendarLexer lexer_;
  parsing::IcalendarParser parser_;
};

TEST_F(IcalendarParserTest, EmptyStream) {
  std::stringstream ss("");
  reader_.SetBuffer(ss.rdbuf());

  parsing::StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<parsing::ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 0);
}

TEST_F(IcalendarParserTest, EmptyCalendar) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n");
  reader_.SetBuffer(ss.rdbuf());

  parsing::StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<parsing::ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);

  parsing::ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  EXPECT_EQ(calendar->name(), "VCALENDAR");
  EXPECT_TRUE(calendar->components().empty());
  EXPECT_TRUE(calendar->properties().empty());
}

TEST_F(IcalendarParserTest, EmptyCalendars) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n"
                       "BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n");
  reader_.SetBuffer(ss.rdbuf());

  parsing::StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<parsing::ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 2);

  for (parsing::ComponentUptr& calendar : stream_components) {
    ASSERT_TRUE(calendar);

    EXPECT_EQ(calendar->name(), "VCALENDAR");
    EXPECT_TRUE(calendar->components().empty());
    EXPECT_TRUE(calendar->properties().empty());
  }
}

TEST_F(IcalendarParserTest, CalendarWithProperties) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "VERSION:2.0\r\n"
                       "PRODID:students.bmstu.ru\r\n"
                       "END:VCALENDAR\r\n");
  reader_.SetBuffer(ss.rdbuf());

  parsing::StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<parsing::ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);
  
  parsing::ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  std::vector<parsing::PropertyUptr>& calendar_properties = calendar->properties();
  ASSERT_EQ(calendar_properties.size(), 2) ;

  std::queue<std::pair<std::string, parsing::IValueUptr>> expected;
  expected.push(std::make_pair(
        "VERSION", std::make_unique<parsing::TextValue>("2.0")));
  expected.push(std::make_pair(
        "PRODID", std::make_unique<parsing::TextValue>("students.bmstu.ru")));
  
  for (parsing::PropertyUptr& property : calendar_properties) {
    std::string expected_name = std::move(expected.front().first);
    parsing::IValueUptr expected_value = std::move(expected.front().second);
    expected.pop();

    parsing::TextValue* expected_text_value
      = dynamic_cast<parsing::TextValue*>(expected_value.get());
    ASSERT_TRUE(expected_text_value);

    ASSERT_TRUE(property);
    EXPECT_EQ(property->name(), expected_name);
    EXPECT_TRUE(property->parameters().empty());

    parsing::IValueUptr& value = property->value();
    ASSERT_TRUE(value);

    parsing::TextValue* text_value = dynamic_cast<parsing::TextValue*>(value.get());
    ASSERT_TRUE(text_value);
    EXPECT_EQ(text_value->text(), expected_text_value->text());
  }

  EXPECT_TRUE(calendar->components().empty());
}

TEST_F(IcalendarParserTest, CalendarWithEmptyEvent) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "VERSION:2.0\r\n"
                       "PRODID:students.bmstu.ru\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "END:VCALENDAR\r\n");
  reader_.SetBuffer(ss.rdbuf());

  parsing::StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<parsing::ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);
  
  parsing::ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  std::vector<parsing::PropertyUptr>& calendar_properties = calendar->properties();
  ASSERT_EQ(calendar_properties.size(), 2) ;

  std::queue<std::pair<std::string, parsing::IValueUptr>> expected;
  expected.push(std::make_pair(
        "VERSION", std::make_unique<parsing::TextValue>("2.0")));
  expected.push(std::make_pair(
        "PRODID", std::make_unique<parsing::TextValue>("students.bmstu.ru")));
  
  for (parsing::PropertyUptr& property : calendar_properties) {
    std::string expected_name = std::move(expected.front().first);
    parsing::IValueUptr expected_value = std::move(expected.front().second);
    expected.pop();

    parsing::TextValue* expected_text_value
      = dynamic_cast<parsing::TextValue*>(expected_value.get());
    ASSERT_TRUE(expected_text_value);

    ASSERT_TRUE(property);
    EXPECT_EQ(property->name(), expected_name);
    EXPECT_TRUE(property->parameters().empty());

    parsing::IValueUptr& value = property->value();
    ASSERT_TRUE(value);

    parsing::TextValue* text_value = dynamic_cast<parsing::TextValue*>(value.get());
    ASSERT_TRUE(text_value);
    EXPECT_EQ(text_value->text(), expected_text_value->text());
  }

  std::vector<parsing::ComponentUptr>& calendar_components = calendar->components();
  ASSERT_EQ(calendar_components.size(), 1) ;

  parsing::ComponentUptr& event = calendar_components[0];
  ASSERT_TRUE(event);

  EXPECT_EQ(event->name(), "VEVENT");
  EXPECT_TRUE(event->properties().empty());
  EXPECT_TRUE(event->components().empty());
}

TEST_F(IcalendarParserTest, CalendarWithEmptyEvents) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "VERSION:2.0\r\n"
                       "PRODID:students.bmstu.ru\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "END:VCALENDAR\r\n");
  reader_.SetBuffer(ss.rdbuf());

  parsing::StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<parsing::ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);
  
  parsing::ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  std::vector<parsing::PropertyUptr>& calendar_properties = calendar->properties();
  ASSERT_EQ(calendar_properties.size(), 2) ;

  std::queue<std::pair<std::string, parsing::IValueUptr>> expected;
  expected.push(std::make_pair(
        "VERSION", std::make_unique<parsing::TextValue>("2.0")));
  expected.push(std::make_pair(
        "PRODID", std::make_unique<parsing::TextValue>("students.bmstu.ru")));
  
  for (parsing::PropertyUptr& property : calendar_properties) {
    std::string expected_name = std::move(expected.front().first);
    parsing::IValueUptr expected_value = std::move(expected.front().second);
    expected.pop();

    parsing::TextValue* expected_text_value
      = dynamic_cast<parsing::TextValue*>(expected_value.get());
    ASSERT_TRUE(expected_text_value);

    ASSERT_TRUE(property);
    EXPECT_EQ(property->name(), expected_name);
    EXPECT_TRUE(property->parameters().empty());

    parsing::IValueUptr& value = property->value();
    ASSERT_TRUE(value);

    parsing::TextValue* text_value = dynamic_cast<parsing::TextValue*>(value.get());
    ASSERT_TRUE(text_value);
    EXPECT_EQ(text_value->text(), expected_text_value->text());
  }

  std::vector<parsing::ComponentUptr>& calendar_components = calendar->components();
  ASSERT_EQ(calendar_components.size(), 2) ;

  for (parsing::ComponentUptr& event : calendar_components) {
    ASSERT_TRUE(event);

    EXPECT_EQ(event->name(), "VEVENT");
    EXPECT_TRUE(event->properties().empty());
    EXPECT_TRUE(event->components().empty());
  }
}

TEST_F(IcalendarParserTest, CalendarWithEvents) {
  std::stringstream ss(
      "BEGIN:VCALENDAR\r\n"
      "VERSION:2.0\r\n"
      "CALSCALE:GREGORIAN\r\n"
      "PRODID:students.bmstu.ru\r\n"
      "METHOD:PUBLISH\r\n"
      "X-WR-CALNAME:Расписание ИУ9-41Б\r\n"
      "X-PUBLISHED-TTL:PT1H\r\n"
      "BEGIN:VEVENT\r\n"
      "UID:64569647f818ecb9b6dc1612\r\n"
      "SUMMARY:Дифференциальные уравнения\r\n"
      "DTSTAMP:20230506T182000Z\r\n"
      "DTSTART:20230211T105000Z\r\n"
      "DTEND:20230211T122500Z\r\n"
      "DESCRIPTION: Бояринов Р. Н.\r\n"
      "LOCATION:505\r\n"
      "RRULE:FREQ=WEEKLY;INTERVAL=1;UNTIL=20230605\r\n"
      "END:VEVENT\r\n"
      "BEGIN:VEVENT\r\n"
      "UID:64569647f818ecb9b6dc1612\r\n"
      "SUMMARY:Дифференциальные уравнения\r\n"
      "DTSTAMP:20230506T182000Z\r\n"
      "DTSTART:20230211T105000Z\r\n"
      "DTEND:20230211T122500Z\r\n"
      "DESCRIPTION: Бояринов Р. Н.\r\n"
      "LOCATION:505\r\n"
      "RRULE:FREQ=WEEKLY;INTERVAL=1;UNTIL=20230605\r\n"
      "END:VEVENT\r\n"
      "END:VCALENDAR\r\n");
  reader_.SetBuffer(ss.rdbuf());

  parsing::StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<parsing::ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);
  
  parsing::ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  std::vector<parsing::PropertyUptr>& calendar_properties = calendar->properties();
  ASSERT_EQ(calendar_properties.size(), 6) ;

  std::queue<std::pair<std::string, parsing::IValueUptr>> expected;
  expected.push(std::make_pair(
        "VERSION", std::make_unique<parsing::TextValue>("2.0")));
  expected.push(std::make_pair(
        "CALSCALE", std::make_unique<parsing::TextValue>("GREGORIAN")));
  expected.push(std::make_pair(
        "PRODID", std::make_unique<parsing::TextValue>("students.bmstu.ru")));
  expected.push(std::make_pair(
        "METHOD", std::make_unique<parsing::TextValue>("PUBLISH")));
  expected.push(std::make_pair(
        "X-WR-CALNAME", std::make_unique<parsing::TextValue>("Расписание ИУ9-41Б")));
  expected.push(std::make_pair(
        "X-PUBLISHED-TTL", std::make_unique<parsing::TextValue>("PT1H")));
  
  for (auto& property : calendar_properties) {
    std::string expected_name = std::move(expected.front().first);
    parsing::IValueUptr expected_value = std::move(expected.front().second);
    expected.pop();

    parsing::TextValue* expected_text_value
      = dynamic_cast<parsing::TextValue*>(expected_value.get());
    ASSERT_TRUE(expected_text_value);

    ASSERT_TRUE(property);
    EXPECT_EQ(property->name(), expected_name);
    EXPECT_TRUE(property->parameters().empty());

    parsing::IValueUptr& value = property->value();
    ASSERT_TRUE(value);

    parsing::TextValue* text_value = dynamic_cast<parsing::TextValue*>(value.get());
    ASSERT_TRUE(text_value);
    EXPECT_EQ(text_value->text(), expected_text_value->text());
  }

  std::vector<parsing::ComponentUptr>& calendar_components = calendar->components();
  ASSERT_EQ(calendar_components.size(), 2) ;

  // свойства первого события
  expected.push(std::make_pair(
        "UID", std::make_unique<parsing::TextValue>("64569647f818ecb9b6dc1612")));
  expected.push(std::make_pair(
        "SUMMARY", std::make_unique<parsing::TextValue>("Дифференциальные уравнения")));
  expected.push(std::make_pair(
        "DTSTAMP", std::make_unique<parsing::TextValue>("20230506T182000Z")));
  expected.push(std::make_pair(
        "DTSTART", std::make_unique<parsing::TextValue>("20230211T105000Z")));
  expected.push(std::make_pair(
        "DTEND", std::make_unique<parsing::TextValue>("20230211T122500Z")));
  expected.push(std::make_pair(
        "DESCRIPTION", std::make_unique<parsing::TextValue>(" Бояринов Р. Н.")));
  expected.push(std::make_pair(
        "LOCATION", std::make_unique<parsing::TextValue>("505")));
  {
    std::vector<parsing::IValueUptr> values;
    values.push_back(std::make_unique<parsing::PairValue>("FREQ", "WEEKLY"));
    values.push_back(std::make_unique<parsing::PairValue>("INTERVAL", "1"));
    values.push_back(std::make_unique<parsing::PairValue>("UNTIL", "20230605"));
    expected.push(std::make_pair(
          "RRULE", std::make_unique<parsing::CompositeValue>(std::move(values))));
  }

  //свойства второго события
  expected.push(std::make_pair(
        "UID", std::make_unique<parsing::TextValue>("64569647f818ecb9b6dc1612")));
  expected.push(std::make_pair(
        "SUMMARY", std::make_unique<parsing::TextValue>("Дифференциальные уравнения")));
  expected.push(std::make_pair(
        "DTSTAMP", std::make_unique<parsing::TextValue>("20230506T182000Z")));
  expected.push(std::make_pair(
        "DTSTART", std::make_unique<parsing::TextValue>("20230211T105000Z")));
  expected.push(std::make_pair(
        "DTEND", std::make_unique<parsing::TextValue>("20230211T122500Z")));
  expected.push(std::make_pair(
        "DESCRIPTION", std::make_unique<parsing::TextValue>(" Бояринов Р. Н.")));
  expected.push(std::make_pair(
        "LOCATION", std::make_unique<parsing::TextValue>("505")));
  {
    std::vector<parsing::IValueUptr> values;
    values.push_back(std::make_unique<parsing::PairValue>("FREQ", "WEEKLY"));
    values.push_back(std::make_unique<parsing::PairValue>("INTERVAL", "1"));
    values.push_back(std::make_unique<parsing::PairValue>("UNTIL", "20230605"));
    expected.push(std::make_pair(
          "RRULE", std::make_unique<parsing::CompositeValue>(std::move(values))));
  }

  for (parsing::ComponentUptr& event : calendar_components) {
    ASSERT_TRUE(event);

    EXPECT_EQ(event->name(), "VEVENT");
    EXPECT_TRUE(event->components().empty());

    std::vector<parsing::PropertyUptr>& event_properties = event->properties();
    ASSERT_EQ(event_properties.size(), 8);

    // цикл идентичен встречавшемуся ранее, но вынести его в
    // в отдельную функцию не получается: тогда макросы gtest
    // не будут работать.
    for (std::size_t i = 0; i < 7 ; i++) {
      std::string expected_name = std::move(expected.front().first);
      parsing::IValueUptr expected_value = std::move(expected.front().second);
      expected.pop();

      parsing::TextValue* expected_text_value
        = dynamic_cast<parsing::TextValue*>(expected_value.get());
      ASSERT_TRUE(expected_text_value);

      parsing::PropertyUptr& property = event_properties[i];
      ASSERT_TRUE(property);
      EXPECT_EQ(property->name(), expected_name);
      EXPECT_TRUE(property->parameters().empty());

      parsing::IValueUptr& value = property->value();
      ASSERT_TRUE(value);

      parsing::TextValue* text_value = dynamic_cast<parsing::TextValue*>(value.get());
      ASSERT_TRUE(text_value);
      EXPECT_EQ(text_value->text(), expected_text_value->text());
    }
    
    // последнее property в теле event отличается
    // по структуре от встречавшихся ранее
    {
      std::string expected_name = std::move(expected.front().first);
      parsing::IValueUptr expected_value = std::move(expected.front().second);
      expected.pop();

      parsing::CompositeValue* expected_composite_value
        = dynamic_cast<parsing::CompositeValue*>(expected_value.get());
      ASSERT_TRUE(expected_composite_value);

      std::vector<parsing::IValueUptr>& expected_values
        = expected_composite_value->values();

      parsing::PropertyUptr& property = event_properties[7];
      ASSERT_TRUE(property);
      EXPECT_EQ(property->name(), expected_name);
      EXPECT_TRUE(property->parameters().empty());

      parsing::IValueUptr& value = property->value();
      ASSERT_TRUE(value);

      parsing::CompositeValue* composite_value
        = dynamic_cast<parsing::CompositeValue*>(value.get());
      ASSERT_TRUE(composite_value);
      
      std::vector<parsing::IValueUptr>& values = composite_value->values();
      ASSERT_EQ(values.size(), expected_values.size());

      for (std::size_t i = 0; i < values.size(); i++) {
        parsing::PairValue* expected_pair_value
          = dynamic_cast<parsing::PairValue*>(expected_values[i].get());
        ASSERT_TRUE(expected_pair_value);

        parsing::PairValue* pair_value
          = dynamic_cast<parsing::PairValue*>(values[i].get());
        ASSERT_TRUE(pair_value);

        ASSERT_EQ(pair_value->name(), expected_pair_value->name());
        ASSERT_EQ(pair_value->text(), expected_pair_value->text());
      }
    }
  }
}
