#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>
#include <queue>

#include "i_char_reader.hpp"
#include "lexer.hpp"
#include "parser.hpp"

// TODO(affeeal): вынести StringStubCharReader и FileCharReader
// в один класс

class StringStubCharReader : public ICharReader {
 public:
  char Peek(std::size_t k = 0) override {
    auto pos = ss_.tellg();
    ss_.seekg(k, ss_.cur);
    char ch = ss_.peek();
    ss_.seekg(pos);
    return ch;
  }

  char Get(std::size_t k = 0) override {
    ss_.seekg(k, ss_.cur);
    return ss_.get();
  }

  bool IsEof() override {
    return (ss_.rdbuf()->in_avail() == 0);
  }

  void set_ss(std::stringstream&& ss) {
    ss_ = std::move(ss);
  }

 private:
  std::stringstream ss_;
};

class iCalendarParserTest : public ::testing::Test {
 protected:
  void SetUp() override {
    lexer_.set_character_reader(char_reader_);
    parser_.set_lexer(lexer_);
  }

  void TearDown() override {
  }

  StringStubCharReader char_reader_;
  iCalendarLexer lexer_;
  iCalendarParser parser_;
};

TEST_F(iCalendarParserTest, EmptyStream) {
  std::stringstream ss("");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 0);
}

TEST_F(iCalendarParserTest, EmptyCalendar) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);

  ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  EXPECT_EQ(calendar->name(), "VCALENDAR");
  EXPECT_TRUE(calendar->components().empty());
  EXPECT_TRUE(calendar->properties().empty());
}

TEST_F(iCalendarParserTest, EmptyCalendars) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n"
                       "BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 2);

  for (ComponentUptr& calendar : stream_components) {
    ASSERT_TRUE(calendar);

    EXPECT_EQ(calendar->name(), "VCALENDAR");
    EXPECT_TRUE(calendar->components().empty());
    EXPECT_TRUE(calendar->properties().empty());
  }
}

TEST_F(iCalendarParserTest, CalendarWithProperties) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "VERSION:2.0\r\n"
                       "PRODID:students.bmstu.ru\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);
  
  ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  std::vector<PropertyUptr>& calendar_properties = calendar->properties();
  ASSERT_EQ(calendar_properties.size(), 2) ;

  std::queue<std::pair<std::string, IValueUptr>> expected;
  expected.push(std::make_pair(
        "VERSION", std::make_unique<TextValue>("2.0")));
  expected.push(std::make_pair(
        "PRODID", std::make_unique<TextValue>("students.bmstu.ru")));
  
  for (PropertyUptr& property : calendar_properties) {
    std::string expected_name = std::move(expected.front().first);
    IValueUptr expected_value = std::move(expected.front().second);
    expected.pop();

    TextValue* expected_text_value
      = dynamic_cast<TextValue*>(expected_value.get());
    ASSERT_TRUE(expected_text_value);

    ASSERT_TRUE(property);
    EXPECT_EQ(property->name(), expected_name);
    EXPECT_TRUE(property->parameters().empty());

    IValueUptr& value = property->value();
    ASSERT_TRUE(value);

    TextValue* text_value = dynamic_cast<TextValue*>(value.get());
    ASSERT_TRUE(text_value);
    EXPECT_EQ(text_value->text(), expected_text_value->text());
  }

  EXPECT_TRUE(calendar->components().empty());
}

TEST_F(iCalendarParserTest, CalendarWithEmptyEvent) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "VERSION:2.0\r\n"
                       "PRODID:students.bmstu.ru\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);
  
  ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  std::vector<PropertyUptr>& calendar_properties = calendar->properties();
  ASSERT_EQ(calendar_properties.size(), 2) ;

  std::queue<std::pair<std::string, IValueUptr>> expected;
  expected.push(std::make_pair(
        "VERSION", std::make_unique<TextValue>("2.0")));
  expected.push(std::make_pair(
        "PRODID", std::make_unique<TextValue>("students.bmstu.ru")));
  
  for (PropertyUptr& property : calendar_properties) {
    std::string expected_name = std::move(expected.front().first);
    IValueUptr expected_value = std::move(expected.front().second);
    expected.pop();

    TextValue* expected_text_value
      = dynamic_cast<TextValue*>(expected_value.get());
    ASSERT_TRUE(expected_text_value);

    ASSERT_TRUE(property);
    EXPECT_EQ(property->name(), expected_name);
    EXPECT_TRUE(property->parameters().empty());

    IValueUptr& value = property->value();
    ASSERT_TRUE(value);

    TextValue* text_value = dynamic_cast<TextValue*>(value.get());
    ASSERT_TRUE(text_value);
    EXPECT_EQ(text_value->text(), expected_text_value->text());
  }

  std::vector<ComponentUptr>& calendar_components = calendar->components();
  ASSERT_EQ(calendar_components.size(), 1) ;

  ComponentUptr& event = calendar_components[0];
  ASSERT_TRUE(event);

  EXPECT_EQ(event->name(), "VEVENT");
  EXPECT_TRUE(event->properties().empty());
  EXPECT_TRUE(event->components().empty());
}

TEST_F(iCalendarParserTest, CalendarWithEmptyEvents) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "VERSION:2.0\r\n"
                       "PRODID:students.bmstu.ru\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);
  
  ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  std::vector<PropertyUptr>& calendar_properties = calendar->properties();
  ASSERT_EQ(calendar_properties.size(), 2) ;

  std::queue<std::pair<std::string, IValueUptr>> expected;
  expected.push(std::make_pair(
        "VERSION", std::make_unique<TextValue>("2.0")));
  expected.push(std::make_pair(
        "PRODID", std::make_unique<TextValue>("students.bmstu.ru")));
  
  for (PropertyUptr& property : calendar_properties) {
    std::string expected_name = std::move(expected.front().first);
    IValueUptr expected_value = std::move(expected.front().second);
    expected.pop();

    TextValue* expected_text_value
      = dynamic_cast<TextValue*>(expected_value.get());
    ASSERT_TRUE(expected_text_value);

    ASSERT_TRUE(property);
    EXPECT_EQ(property->name(), expected_name);
    EXPECT_TRUE(property->parameters().empty());

    IValueUptr& value = property->value();
    ASSERT_TRUE(value);

    TextValue* text_value = dynamic_cast<TextValue*>(value.get());
    ASSERT_TRUE(text_value);
    EXPECT_EQ(text_value->text(), expected_text_value->text());
  }

  std::vector<ComponentUptr>& calendar_components = calendar->components();
  ASSERT_EQ(calendar_components.size(), 2) ;

  for (ComponentUptr& event : calendar_components) {
    ASSERT_TRUE(event);

    EXPECT_EQ(event->name(), "VEVENT");
    EXPECT_TRUE(event->properties().empty());
    EXPECT_TRUE(event->components().empty());
  }
}

TEST_F(iCalendarParserTest, CalendarWithEvents) {
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
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();
  ASSERT_TRUE(root);

  std::vector<ComponentUptr>& stream_components = root->components();
  ASSERT_EQ(stream_components.size(), 1);
  
  ComponentUptr& calendar = stream_components[0];
  ASSERT_TRUE(calendar);

  std::vector<PropertyUptr>& calendar_properties = calendar->properties();
  ASSERT_EQ(calendar_properties.size(), 6) ;

  std::queue<std::pair<std::string, IValueUptr>> expected;
  expected.push(std::make_pair(
        "VERSION", std::make_unique<TextValue>("2.0")));
  expected.push(std::make_pair(
        "CALSCALE", std::make_unique<TextValue>("GREGORIAN")));
  expected.push(std::make_pair(
        "PRODID", std::make_unique<TextValue>("students.bmstu.ru")));
  expected.push(std::make_pair(
        "METHOD", std::make_unique<TextValue>("PUBLISH")));
  expected.push(std::make_pair(
        "X-WR-CALNAME", std::make_unique<TextValue>("Расписание ИУ9-41Б")));
  expected.push(std::make_pair(
        "X-PUBLISHED-TTL", std::make_unique<TextValue>("PT1H")));
  
  for (auto& property : calendar_properties) {
    std::string expected_name = std::move(expected.front().first);
    IValueUptr expected_value = std::move(expected.front().second);
    expected.pop();

    TextValue* expected_text_value
      = dynamic_cast<TextValue*>(expected_value.get());
    ASSERT_TRUE(expected_text_value);

    ASSERT_TRUE(property);
    EXPECT_EQ(property->name(), expected_name);
    EXPECT_TRUE(property->parameters().empty());

    IValueUptr& value = property->value();
    ASSERT_TRUE(value);

    TextValue* text_value = dynamic_cast<TextValue*>(value.get());
    ASSERT_TRUE(text_value);
    EXPECT_EQ(text_value->text(), expected_text_value->text());
  }

  std::vector<ComponentUptr>& calendar_components = calendar->components();
  ASSERT_EQ(calendar_components.size(), 2) ;

  // свойства первого события
  expected.push(std::make_pair(
        "UID", std::make_unique<TextValue>("64569647f818ecb9b6dc1612")));
  expected.push(std::make_pair(
        "SUMMARY", std::make_unique<TextValue>("Дифференциальные уравнения")));
  expected.push(std::make_pair(
        "DTSTAMP", std::make_unique<TextValue>("20230506T182000Z")));
  expected.push(std::make_pair(
        "DTSTART", std::make_unique<TextValue>("20230211T105000Z")));
  expected.push(std::make_pair(
        "DTEND", std::make_unique<TextValue>("20230211T122500Z")));
  expected.push(std::make_pair(
        "DESCRIPTION", std::make_unique<TextValue>(" Бояринов Р. Н.")));
  expected.push(std::make_pair(
        "LOCATION", std::make_unique<TextValue>("505")));
  {
    std::vector<IValueUptr> values;
    values.push_back(std::make_unique<PairValue>("FREQ", "WEEKLY"));
    values.push_back(std::make_unique<PairValue>("INTERVAL", "1"));
    values.push_back(std::make_unique<PairValue>("UNTIL", "20230605"));
    expected.push(std::make_pair(
          "RRULE", std::make_unique<CompositeValue>(std::move(values))));
  }

  //свойства второго события
  expected.push(std::make_pair(
        "UID", std::make_unique<TextValue>("64569647f818ecb9b6dc1612")));
  expected.push(std::make_pair(
        "SUMMARY", std::make_unique<TextValue>("Дифференциальные уравнения")));
  expected.push(std::make_pair(
        "DTSTAMP", std::make_unique<TextValue>("20230506T182000Z")));
  expected.push(std::make_pair(
        "DTSTART", std::make_unique<TextValue>("20230211T105000Z")));
  expected.push(std::make_pair(
        "DTEND", std::make_unique<TextValue>("20230211T122500Z")));
  expected.push(std::make_pair(
        "DESCRIPTION", std::make_unique<TextValue>(" Бояринов Р. Н.")));
  expected.push(std::make_pair(
        "LOCATION", std::make_unique<TextValue>("505")));
  {
    std::vector<IValueUptr> values;
    values.push_back(std::make_unique<PairValue>("FREQ", "WEEKLY"));
    values.push_back(std::make_unique<PairValue>("INTERVAL", "1"));
    values.push_back(std::make_unique<PairValue>("UNTIL", "20230605"));
    expected.push(std::make_pair(
          "RRULE", std::make_unique<CompositeValue>(std::move(values))));
  }

  for (ComponentUptr& event : calendar_components) {
    ASSERT_TRUE(event);

    EXPECT_EQ(event->name(), "VEVENT");
    EXPECT_TRUE(event->components().empty());

    std::vector<PropertyUptr>& event_properties = event->properties();
    ASSERT_EQ(event_properties.size(), 8);

    // цикл идентичен встречавшемуся ранее, но вынести его в
    // в отдельную функцию не получается: тогда макросы gtest
    // не будут работать.
    for (std::size_t i = 0; i < 7 ; i++) {
      std::string expected_name = std::move(expected.front().first);
      IValueUptr expected_value = std::move(expected.front().second);
      expected.pop();

      TextValue* expected_text_value
        = dynamic_cast<TextValue*>(expected_value.get());
      ASSERT_TRUE(expected_text_value);

      PropertyUptr& property = event_properties[i];
      ASSERT_TRUE(property);
      EXPECT_EQ(property->name(), expected_name);
      EXPECT_TRUE(property->parameters().empty());

      IValueUptr& value = property->value();
      ASSERT_TRUE(value);

      TextValue* text_value = dynamic_cast<TextValue*>(value.get());
      ASSERT_TRUE(text_value);
      EXPECT_EQ(text_value->text(), expected_text_value->text());
    }
    
    // последнее property в теле event отличается
    // по структуре от встречавшихся ранее
    {
      std::string expected_name = std::move(expected.front().first);
      IValueUptr expected_value = std::move(expected.front().second);
      expected.pop();

      CompositeValue* expected_composite_value
        = dynamic_cast<CompositeValue*>(expected_value.get());
      ASSERT_TRUE(expected_composite_value);

      std::vector<IValueUptr>& expected_values
        = expected_composite_value->values();

      PropertyUptr& property = event_properties[7];
      ASSERT_TRUE(property);
      EXPECT_EQ(property->name(), expected_name);
      EXPECT_TRUE(property->parameters().empty());

      IValueUptr& value = property->value();
      ASSERT_TRUE(value);

      CompositeValue* composite_value
        = dynamic_cast<CompositeValue*>(value.get());
      ASSERT_TRUE(composite_value);
      
      std::vector<IValueUptr>& values = composite_value->values();
      ASSERT_EQ(values.size(), expected_values.size());

      for (std::size_t i = 0; i < values.size(); i++) {
        PairValue* expected_pair_value
          = dynamic_cast<PairValue*>(expected_values[i].get());
        ASSERT_TRUE(expected_pair_value);

        PairValue* pair_value
          = dynamic_cast<PairValue*>(values[i].get());
        ASSERT_TRUE(pair_value);

        ASSERT_EQ(pair_value->name(), expected_pair_value->name());
        ASSERT_EQ(pair_value->text(), expected_pair_value->text());
      }
    }
  }
}
