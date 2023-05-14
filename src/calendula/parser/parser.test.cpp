#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "parser.hpp"

// TODO: удалить дублирование

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

  std::vector<ComponentUptr>& stream_comps = root->components();
  EXPECT_EQ(stream_comps.size(), 0);
}

TEST_F(iCalendarParserTest, EmptyCalendar) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();

  std::vector<ComponentUptr>& stream_comps = root->components();
  ASSERT_EQ(stream_comps.size(), 1);

  ComponentUptr& cal_0 = stream_comps[0];
  ASSERT_TRUE(cal_0);

  EXPECT_EQ(cal_0->name(), "VCALENDAR");
  EXPECT_TRUE(cal_0->properties().empty());
  EXPECT_TRUE(cal_0->components().empty());
}

TEST_F(iCalendarParserTest, EmptyCalendars) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n"
                       "BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();

  std::vector<ComponentUptr>& stream_comps = root->components();
  ASSERT_EQ(stream_comps.size(), 2);

  ComponentUptr& cal_0 = stream_comps[0];
  ASSERT_TRUE(cal_0);

  EXPECT_EQ(cal_0->name(), "VCALENDAR");
  EXPECT_TRUE(cal_0->properties().empty());
  EXPECT_TRUE(cal_0->components().empty());

  ComponentUptr& cal_1 = stream_comps[1];
  ASSERT_TRUE(cal_1);

  EXPECT_EQ(cal_1->name(), "VCALENDAR");
  EXPECT_TRUE(cal_1->properties().empty());
  EXPECT_TRUE(cal_1->components().empty());
}

TEST_F(iCalendarParserTest, CalendarWithProperty) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "VERSION:2.0\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();

  std::vector<ComponentUptr>& stream_comps = root->components();
  ASSERT_EQ(stream_comps.size(), 1);

  ComponentUptr& cal_0 = stream_comps[0];
  ASSERT_TRUE(cal_0);

  std::vector<PropertyUptr>& cal_0_props = cal_0->properties();
  ASSERT_EQ(cal_0_props.size(), 1) ;

  PropertyUptr& cal_0_prop_0 = cal_0_props[0];
  ASSERT_TRUE(cal_0_prop_0);

  EXPECT_EQ(cal_0_prop_0->name(), "VERSION");
  IValueUptr& value_0 = cal_0_prop_0->value();
  ASSERT_TRUE(value_0);
  TextValue* value_0_text = dynamic_cast<TextValue*>(value_0.get());
  ASSERT_TRUE(value_0_text);
  EXPECT_EQ(value_0_text->text(), "2.0");
}

TEST_F(iCalendarParserTest, CalendarWithProperties) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "VERSION:2.0\r\n"
                       "CALSCALE:GREGORIAN\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();

  std::vector<ComponentUptr>& stream_comps = root->components();
  ASSERT_EQ(stream_comps.size(), 1);

  ComponentUptr& cal_0 = stream_comps[0];
  ASSERT_TRUE(cal_0);

  std::vector<PropertyUptr>& cal_0_props = cal_0->properties();
  ASSERT_EQ(cal_0_props.size(), 2) ;

  PropertyUptr& cal_0_prop_0 = cal_0_props[0];
  ASSERT_TRUE(cal_0_prop_0);

  EXPECT_EQ(cal_0_prop_0->name(), "VERSION");
  IValueUptr& value_0 = cal_0_prop_0->value();
  ASSERT_TRUE(value_0);
  TextValue* value_0_text = dynamic_cast<TextValue*>(value_0.get());
  ASSERT_TRUE(value_0_text);
  EXPECT_EQ(value_0_text->text(), "2.0");

  PropertyUptr& cal_0_prop_1 = cal_0_props[1];
  ASSERT_TRUE(cal_0_prop_1);

  EXPECT_EQ(cal_0_prop_1->name(), "CALSCALE");
  IValueUptr& value_1 = cal_0_prop_1->value();
  ASSERT_TRUE(value_1);
  TextValue* value_1_text = dynamic_cast<TextValue*>(value_1.get());
  ASSERT_TRUE(value_1_text);
  EXPECT_EQ(value_1_text->text(), "GREGORIAN");
}

TEST_F(iCalendarParserTest, CalendarWithEmptyEvent) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();

  std::vector<ComponentUptr>& stream_comps = root->components();
  ASSERT_EQ(stream_comps.size(), 1);
  
  ComponentUptr& cal_0 = stream_comps[0];
  ASSERT_TRUE(cal_0);

  std::vector<ComponentUptr>& cal_0_comps = cal_0->components();
  ASSERT_EQ(cal_0_comps.size(), 1) ;

  ComponentUptr& cal_0_event_0 = cal_0_comps[0];
  ASSERT_TRUE(cal_0_event_0);
  EXPECT_EQ(cal_0_event_0->name(), "VEVENT");
  EXPECT_TRUE(cal_0_event_0->components().empty());
  EXPECT_TRUE(cal_0_event_0->properties().empty());
}

TEST_F(iCalendarParserTest, CalendarWithEmptyEvents) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "BEGIN:VEVENT\r\n"
                       "END:VEVENT\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));

  StreamUptr root = parser_.Parse();

  std::vector<ComponentUptr>& stream_comps = root->components();
  ASSERT_EQ(stream_comps.size(), 1);
  
  ComponentUptr& cal_0 = stream_comps[0];
  ASSERT_TRUE(cal_0);

  std::vector<ComponentUptr>& cal_0_comps = cal_0->components();
  ASSERT_EQ(cal_0_comps.size(), 2) ;

  ComponentUptr& cal_0_event_0 = cal_0_comps[0];
  ASSERT_TRUE(cal_0_event_0);
  EXPECT_EQ(cal_0_event_0->name(), "VEVENT");
  EXPECT_TRUE(cal_0_event_0->components().empty());
  EXPECT_TRUE(cal_0_event_0->properties().empty());

  ComponentUptr& cal_0_event_1 = cal_0_comps[1];
  ASSERT_TRUE(cal_0_event_1);
  EXPECT_EQ(cal_0_event_1->name(), "VEVENT");
  EXPECT_TRUE(cal_0_event_1->components().empty());
  EXPECT_TRUE(cal_0_event_1->properties().empty());
}
