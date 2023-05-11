#include <gtest/gtest.h>

#include <fstream>

#include "character_reader.hpp"

const std::string kPath = "../../../../data/";

TEST(FileCharacterReaderTest, EmptyFile) {
  std::ifstream f(kPath + "empty.ics");
  FileCharacterReader fcr(std::move(f));

  EXPECT_EQ(fcr.IsEof(), true);

  // у пустого потока вызовы Peek и Get возвращают std::string::npos
  EXPECT_EQ(fcr.Peek(), std::string::npos);
  EXPECT_EQ(fcr.Peek(1), std::string::npos);
  EXPECT_EQ(fcr.Get(), std::string::npos);
  EXPECT_EQ(fcr.Get(1), std::string::npos);
}

TEST(FileCharacterReaderTest, NonEmptyFile) {
  std::ifstream f(kPath + "bmstu_schedule.ics");
  FileCharacterReader fcr(std::move(f));

  EXPECT_EQ(fcr.IsEof(), false);

  // первая строка bmstu_schedule.ics:
  // BEGIN:VCALENDAR

  // заглянуть за символом
  EXPECT_EQ(fcr.Peek(), 'B');

  // при повторном заглядывании тот же результат
  EXPECT_EQ(fcr.Peek(), 'B');

  // забрать символ из потока
  EXPECT_EQ(fcr.Get(), 'B');
  
  EXPECT_EQ(fcr.Peek(), 'E');

  // заглянуть за k-тым символом потока
  EXPECT_EQ(fcr.Peek(2), 'I');

  EXPECT_EQ(fcr.Peek(), 'E');

  // пропустить k-1 символ потока и вернуть k-тый 
  EXPECT_EQ(fcr.Get(3), 'N');

  EXPECT_EQ(fcr.Peek(), ':');
}
