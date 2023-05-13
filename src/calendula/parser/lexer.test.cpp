#include <gtest/gtest.h>

#include <cstddef>
#include <sstream>
#include <string>

#include "character_reader.hpp"
#include "lexer.hpp"

class StringStubCharReader : public ICharacterReader {
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

class iCalendarLexerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    lexer_ = iCalendarLexer();
    lexer_.set_character_reader(char_reader_);
  }

  void TearDown() override {
  }

  StringStubCharReader char_reader_;
  iCalendarLexer lexer_;
};

TEST_F(iCalendarLexerTest, EmptyCalendarStream) {
  std::stringstream ss("");
  char_reader_.set_ss(std::move(ss));
  
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kEof, ""));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kEof, ""));
}

TEST_F(iCalendarLexerTest, EmptyCalendarBody) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n"
                       "END:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));
  
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "BEGIN"));
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kDelimiter, ":"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, ":"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kDelimiter, "\r"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "\r"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "\n"));

  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kIdentifier, "END"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "END"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, ":"));
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "\r"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "\n"));

  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kEof));
}

TEST_F(iCalendarLexerTest, CommonLine) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n");
  char_reader_.set_ss(std::move(ss));
  
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "BEGIN"));
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kDelimiter, ":"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, ":"));
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kDelimiter, "\r"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "\r"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "\n"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kEof));
}

TEST_F(iCalendarLexerTest, LineWithParameters) {
  std::stringstream ss("RRULE:FREQ=WEEKLY;INTERVAL=2;UNTIL=20230605\r\n");
  char_reader_.set_ss(std::move(ss));

  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "RRULE"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, ":"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "FREQ"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "="));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "WEEKLY"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, ";"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "INTERVAL"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "="));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "2"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, ";"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "UNTIL"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "="));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "20230605"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "\r"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kDelimiter, "\n"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kEof));
}
