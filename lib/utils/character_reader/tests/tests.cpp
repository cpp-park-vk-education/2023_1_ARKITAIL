#include <gtest/gtest.h>

#include <fstream>

#include "FileCharacterReader.hpp"

const std::string kPath = "../../../../data/";

TEST(FileCharacterReaderTest, EmptyFile) {
  std::ifstream fs(kPath + "empty.ics");
  FileCharacterReader char_reader(std::move(fs));

  EXPECT_EQ(char_reader.IsEof(), true);

  // у пустого потока вызовы Peek и Get возвращают std::string::npos
  EXPECT_EQ(char_reader.Peek(), std::string::npos);
  EXPECT_EQ(char_reader.Peek(1), std::string::npos);
  EXPECT_EQ(char_reader.Get(), std::string::npos);
  EXPECT_EQ(char_reader.Get(1), std::string::npos);
}

TEST(FileCharacterReaderTest, NonEmptyFile) {
  std::ifstream fs(kPath + "bmstu_schedule.ics");
  FileCharacterReader char_reader(std::move(fs));

  EXPECT_EQ(char_reader.IsEof(), false);

  // первая строка bmstu_schedule.ics:
  // BEGIN:VCALENDAR

  // заглянуть за символом
  EXPECT_EQ(char_reader.Peek(), 'B');

  // при повторном заглядывании тот же результат
  EXPECT_EQ(char_reader.Peek(), 'B');

  // забрать символ из потока
  EXPECT_EQ(char_reader.Get(), 'B');
  
  EXPECT_EQ(char_reader.Peek(), 'E');

  // заглянуть за k-тым символом потока
  EXPECT_EQ(char_reader.Peek(2), 'I');

  EXPECT_EQ(char_reader.Peek(), 'E');

  // пропустить k-1 символ потока и вернуть k-тый 
  EXPECT_EQ(char_reader.Get(3), 'N');

  EXPECT_EQ(char_reader.Peek(), ':');
}
