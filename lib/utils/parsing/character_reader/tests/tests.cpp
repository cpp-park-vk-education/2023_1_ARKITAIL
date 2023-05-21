#include <gtest/gtest.h>

#include <sstream>
#include <streambuf>
#include <string>

#include "IstreamCharacterReader.hpp"

TEST(IstreamCharacterReaderTest, Empty) {
  std::stringstream ss("");
  IstreamCharacterReader reader(ss.rdbuf());

  EXPECT_EQ(reader.IsEof(), true);

  // у пустого потока вызовы Peek и Get возвращают std::string::npos
  EXPECT_EQ(reader.Peek(), std::string::npos);
  EXPECT_EQ(reader.Peek(1), std::string::npos);
  EXPECT_EQ(reader.Get(), std::string::npos);
  EXPECT_EQ(reader.Get(1), std::string::npos);
}

TEST(FileCharacterReaderTest, NonEmpty) {
  std::stringstream ss("BEGIN:VCALENDAR\r\n");
  IstreamCharacterReader reader(ss.rdbuf());

  EXPECT_EQ(reader.IsEof(), false);

  EXPECT_EQ(reader.Peek(), 'B');

  // при повторном заглядывании тот же результат
  EXPECT_EQ(reader.Peek(), 'B');

  EXPECT_EQ(reader.Get(), 'B');
  EXPECT_EQ(reader.Peek(), 'E');

  // заглянуть за k-тым символом потока
  EXPECT_EQ(reader.Peek(2), 'I');
  EXPECT_EQ(reader.Peek(), 'E');

  // пропустить k-1 символ потока и вернуть k-тый 
  EXPECT_EQ(reader.Get(3), 'N');
  EXPECT_EQ(reader.Peek(), ':');
}
