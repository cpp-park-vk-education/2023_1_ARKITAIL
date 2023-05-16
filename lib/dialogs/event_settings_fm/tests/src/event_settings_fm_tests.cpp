#include <memory>
#include <string>

#include <gtest/gtest.h>

#include <string>

#include <Wt/WDate.h>
#include <Wt/WTime.h>

#include "event.hpp"
#include "event_settings_fm.hpp"

const std::string kEmpty = "";

const std::string kTitle = "title";
const std::string kDescription = "description";
const std::string kCalendar = "calendar";

const Wt::WDate kBeginTime(9, 22, 51);
const Wt::WDate kBeginDate(2023, 5, 4);
const Wt::WTime kEndTime(12, 17, 0);
const Wt::WTime kEndDate(2023, 5, 11);

const Repeat kRepeat = Repeat::kWeek;
const Wt::WDate kUntil(2023, 5, 20);
const int kInterval = 3;
const int kIntervalNegative = -2;

TEST(EventSettingsFMTest, EmptyFailed) {
  auto event = std::make_unique<Event>();

  auto event_settings_fm = std::make_unique<EventSettingsFM>();
  event_settings_fm->SetData(std::move(event));

  EXPECT_FALSE(event_settings_fm->validate());
}

TEST(EventSettingsFMTest, EmptyTitleFailed) {
  auto event = std::make_unique<Event>(
      kEmpty, kDescription, kCalendar,
      kBeginTime, kBeginDate, kEndTime, kEndDate,
      kRepeat, kUntil, kInterval);

  auto event_settings_fm = std::make_unique<EventSettingsFM>();
  event_settings_fm->SetData(std::move(event));

  EXPECT_FALSE(event_settings_fm->validate());
}

TEST(EventSettingsFMTest, EndDateEarlierThanBeginDateFailed) {
  auto event = std::make_unique<Event>(
      kTitle, kDescription, kCalendar,
      kBeginTime, kEndDate, kEndTime, kBeginDate,
      kRepeat, kUntil, kInterval);

  auto event_settings_fm = std::make_unique<EventSettingsFM>();
  event_settings_fm->SetData(std::move(event));

  EXPECT_FALSE(event_settings_fm->validate());
}

TEST(EventSettingsFMTest, NegativeIntervalFailed) {
  auto event = std::make_unique<Event>(
      kTitle, kDescription, kCalendar,
      kBeginTime, kBeginDate, kEndTime, kEndDate,
      kRepeat, kUntil, kIntervalNegative);

  auto event_settings_fm = std::make_unique<EventSettingsFM>();
  event_settings_fm->SetData(std::move(event));

  EXPECT_FALSE(event_settings_fm->validate());
}

TEST(EventSettingsFMTest, AllFiledsOk) {
  auto event = std::make_unique<Event>(
      kTitle, kDescription, kCalendar,
      kBeginTime, kBeginDate, kEndTime, kEndDate,
      kRepeat, kUntil, kInterval);

  auto event_settings_fm = std::make_unique<EventSettingsFM>();
  event_settings_fm->SetData(std::move(event));

  EXPECT_TRUE(event_settings_fm->validate());
}
