#include <algorithm>
#include <gtest/gtest.h>

#include "calendar.hpp"
#include "calendar_settings_fm.hpp"

const std::string kEmpty = "";
const std::string kTitle = "title";
const std::string kDescription = "description";
const std::string kColor = "#000000";
const std::string kVisibility = "public";

TEST(CalendarSettingsFMTest, EmptyFailed) {
  auto calendar = std::make_unique<Calendar>();
  auto calendar_settings_fm = std::make_unique<CalendarSettingsFM>();
  calendar_settings_fm->SetData(std::move(calendar));

  EXPECT_FALSE(calendar_settings_fm->validate());
}

TEST(CalendarSettingsFMTest, EmptyTitleFailed) {
  auto calendar = std::make_unique<Calendar>(
      kEmpty, kDescription, kColor, kVisibility);
  auto calendar_settings_fm = std::make_unique<CalendarSettingsFM>();
  calendar_settings_fm->SetData(std::move(calendar));

  EXPECT_FALSE(calendar_settings_fm->validate());
}

TEST(CalendarSettingsFMTest, EmptyDescriptionOk) {
  auto calendar = std::make_unique<Calendar>(
      kTitle, kEmpty, kColor, kVisibility);
  auto calendar_settings_fm = std::make_unique<CalendarSettingsFM>();
  calendar_settings_fm->SetData(std::move(calendar));

  EXPECT_TRUE(calendar_settings_fm->validate());
}

TEST(CalendarSettingsFMTest, AllFieldsOk) {
  auto calendar = std::make_unique<Calendar>(
      kTitle, kDescription, kColor, kVisibility);
  auto calendar_settings_fm = std::make_unique<CalendarSettingsFM>();
  calendar_settings_fm->SetData(std::move(calendar));

  EXPECT_TRUE(calendar_settings_fm->validate());
}
