#include <gtest/gtest.h>

#include <cstddef>
#include <sstream>
#include <string>

#include "IstreamCharacterReader.hpp"
#include "Lexer.hpp"

class IcalendarLexerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    lexer_.set_character_reader(reader_);
  }

  void TearDown() override {
  }

  parsing::IstreamCharacterReader reader_;
  parsing::IcalendarLexer lexer_;
};

TEST_F(IcalendarLexerTest, Empty) {
  std::stringstream ss("");
  reader_.SetBuffer(ss.rdbuf());
  
  EXPECT_EQ(lexer_.Peek(), parsing::Lexem(parsing::Tag::kEof, ""));
  EXPECT_EQ(lexer_.Get(), parsing::Lexem(parsing::Tag::kEof, ""));
}

TEST_F(IcalendarLexerTest, CommonLine) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n");
  reader_.SetBuffer(ss.rdbuf());
  
  EXPECT_EQ(lexer_.Get(), parsing::kBegin);
  EXPECT_EQ(lexer_.Peek(), parsing::kColon);
  EXPECT_EQ(lexer_.Get(), parsing::kColon);
  EXPECT_EQ(lexer_.Peek(), parsing::Lexem(parsing::Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Get(), parsing::Lexem(parsing::Tag::kIdentifier, "VCALENDAR"));
  EXPECT_EQ(lexer_.Peek(), parsing::kCarriageReturn);
  EXPECT_EQ(lexer_.Get(), parsing::kCarriageReturn);
  EXPECT_EQ(lexer_.Get(), parsing::kLineFeed);
  EXPECT_EQ(lexer_.Get(), parsing::kEof);
}

TEST_F(IcalendarLexerTest, LineWithParameters) {
  std::stringstream ss("RRULE:FREQ=WEEKLY;UNTIL=20230605\r\n");
  reader_.SetBuffer(ss.rdbuf());

  EXPECT_EQ(lexer_.Get(), parsing::Lexem(parsing::Tag::kIdentifier, "RRULE"));
  EXPECT_EQ(lexer_.Get(), parsing::kColon);
  EXPECT_EQ(lexer_.Get(), parsing::Lexem(parsing::Tag::kIdentifier, "FREQ"));
  EXPECT_EQ(lexer_.Get(), parsing::kEqual);
  EXPECT_EQ(lexer_.Get(), parsing::Lexem(parsing::Tag::kIdentifier, "WEEKLY"));
  EXPECT_EQ(lexer_.Get(), parsing::kSemicolon);
  EXPECT_EQ(lexer_.Get(), parsing::Lexem(parsing::Tag::kIdentifier, "UNTIL"));
  EXPECT_EQ(lexer_.Get(), parsing::kEqual);
  EXPECT_EQ(lexer_.Get(), parsing::Lexem(parsing::Tag::kIdentifier, "20230605"));
  EXPECT_EQ(lexer_.Get(), parsing::kCarriageReturn);
  EXPECT_EQ(lexer_.Get(), parsing::kLineFeed);
  EXPECT_EQ(lexer_.Get(), parsing::kEof);
}

TEST_F(IcalendarLexerTest, RequestKthLexem) {
  std::stringstream ss("RRULE:FREQ=MONTHLY\r\n");
  reader_.SetBuffer(ss.rdbuf());

  EXPECT_EQ(lexer_.Get(1), parsing::kColon);
  EXPECT_EQ(lexer_.Peek(), parsing::Lexem(parsing::Tag::kIdentifier, "FREQ"));
  EXPECT_EQ(lexer_.Peek(1), parsing::kEqual);
  EXPECT_EQ(lexer_.Get(2), parsing::Lexem(parsing::Tag::kIdentifier, "MONTHLY"));
  EXPECT_EQ(lexer_.Get(), parsing::kCarriageReturn);
  EXPECT_EQ(lexer_.Peek(1), parsing::kEof);
  EXPECT_EQ(lexer_.Get(), parsing::kLineFeed);
  EXPECT_EQ(lexer_.Get(), parsing::kEof);
}
