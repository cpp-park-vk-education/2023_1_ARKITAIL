#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "IstreamReader.hpp"
#include "IcalendarLexer.hpp"

namespace lexer {
class IcalendarLexerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    lexer_.set_reader(reader_);
  }

  void TearDown() override {
  }

  reader::IstreamReader reader_;
  IcalendarLexer lexer_;
};

TEST_F(IcalendarLexerTest, Empty) {
  std::stringstream source("");
  reader_.set_source(std::make_unique<std::stringstream>(std::move(source)));
  
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kEof, ""));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kEof, ""));
}

TEST_F(IcalendarLexerTest, CommonLine) {
  std::stringstream source("BEGIN:VCALENDAR\r\n");
  reader_.set_source(std::make_unique<std::stringstream>(std::move(source)));
  
  EXPECT_EQ(lexer_.Get(), kBegin);
  EXPECT_EQ(lexer_.Peek(), kColon);
  EXPECT_EQ(lexer_.Get(), kColon);
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Peek(), kCarriageReturn);
  EXPECT_EQ(lexer_.Get(), kCarriageReturn);
  EXPECT_EQ(lexer_.Get(), kLineFeed);
  EXPECT_EQ(lexer_.Get(), kEof);
}

TEST_F(IcalendarLexerTest, LineWithParameters) {
  std::stringstream source("RRULE:FREQ=WEEKLY;UNTIL=20230605\r\n");
  reader_.set_source(std::make_unique<std::stringstream>(std::move(source)));

  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "RRULE"));
  EXPECT_EQ(lexer_.Get(), kColon);
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "FREQ"));
  EXPECT_EQ(lexer_.Get(), kEqual);
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "WEEKLY"));
  EXPECT_EQ(lexer_.Get(), kSemicolon);
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "UNTIL"));
  EXPECT_EQ(lexer_.Get(), kEqual);
  EXPECT_EQ(lexer_.Get(), Lexem(Tag::kIdentifier, "20230605"));
  EXPECT_EQ(lexer_.Get(), kCarriageReturn);
  EXPECT_EQ(lexer_.Get(), kLineFeed);
  EXPECT_EQ(lexer_.Get(), kEof);
}

TEST_F(IcalendarLexerTest, RequestKthLexem) {
  std::stringstream source("RRULE:FREQ=MONTHLY\r\n");
  reader_.set_source(std::make_unique<std::stringstream>(std::move(source)));

  EXPECT_EQ(lexer_.Get(1), kColon);
  EXPECT_EQ(lexer_.Peek(), Lexem(Tag::kIdentifier, "FREQ"));
  EXPECT_EQ(lexer_.Peek(1), kEqual);
  EXPECT_EQ(lexer_.Get(2), Lexem(Tag::kIdentifier, "MONTHLY"));
  EXPECT_EQ(lexer_.Get(), kCarriageReturn);
  EXPECT_EQ(lexer_.Peek(1), kEof);
  EXPECT_EQ(lexer_.Get(), kLineFeed);
  EXPECT_EQ(lexer_.Get(), kEof);
}
} // namespace lexer
