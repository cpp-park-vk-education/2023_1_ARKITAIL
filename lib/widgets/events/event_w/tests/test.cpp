#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "EventW.hpp"

class EventWTest : public ::testing::Test {
  protected:
    void SetUp() override {
        large_events_ = {EventW(0, "Title0", Wt::WColor(200, 50, 50, 50),
                                Wt::WDateTime(Wt::WDate(2023, 5, 21), Wt::WTime(12, 45)),
                                Wt::WDateTime(Wt::WDate(2023, 5, 27), Wt::WTime(14, 0))),

                         EventW(1, "Title1", Wt::WColor(50, 20, 220, 50),
                                Wt::WDateTime(Wt::WDate(2023, 2, 25), Wt::WTime(12, 45)),
                                Wt::WDateTime(Wt::WDate(2023, 5, 29), Wt::WTime(14, 0))),

                         EventW(2, "Title2", Wt::WColor(250, 20, 220, 50),
                                Wt::WDateTime(Wt::WDate(2023, 5, 20), Wt::WTime(12, 45)),
                                Wt::WDateTime(Wt::WDate(2023, 9, 30), Wt::WTime(14, 0))),

                         EventW(3, "Title3", Wt::WColor(25, 20, 220, 50),
                                Wt::WDateTime(Wt::WDate(2023, 1, 25), Wt::WTime(12, 45)),
                                Wt::WDateTime(Wt::WDate(2023, 5, 25), Wt::WTime(14, 0))),

                         EventW(4, "Title4", Wt::WColor(25, 200, 220, 50),
                                Wt::WDateTime(Wt::WDate(2023, 5, 27), Wt::WTime(0, 0)),
                                Wt::WDateTime(Wt::WDate(2024, 5, 27), Wt::WTime(23, 59)))};

        small_events_ = {EventW(0, "Title0", Wt::WColor(200, 50, 50, 50),
                                Wt::WDateTime(Wt::WDate(2023, 5, 27), Wt::WTime(12, 45)),
                                Wt::WDateTime(Wt::WDate(2023, 5, 27), Wt::WTime(14, 0))),

                         EventW(1, "Title1", Wt::WColor(50, 20, 220, 50),
                                Wt::WDateTime(Wt::WDate(2023, 2, 25), Wt::WTime(10, 45)),
                                Wt::WDateTime(Wt::WDate(2023, 2, 25), Wt::WTime(19, 10))),

                         EventW(2, "Title2", Wt::WColor(250, 20, 220, 50),
                                Wt::WDateTime(Wt::WDate(2023, 9, 2), Wt::WTime(0, 45)),
                                Wt::WDateTime(Wt::WDate(2023, 9, 2), Wt::WTime(14, 0))),

                         EventW(3, "Title3", Wt::WColor(25, 20, 220, 50),
                                Wt::WDateTime(Wt::WDate(2023, 1, 25), Wt::WTime(0, 0)),
                                Wt::WDateTime(Wt::WDate(2023, 1, 25), Wt::WTime(23, 59))),

                         EventW(4, "Title4", Wt::WColor(25, 200, 220, 50),
                                Wt::WDateTime(Wt::WDate(2023, 7, 27), Wt::WTime(0, 8)),
                                Wt::WDateTime(Wt::WDate(2024, 7, 27), Wt::WTime(20, 59)))};
    }

    void TearDown() override {}

    std::vector<EventW> small_events_;
    std::vector<EventW> large_events_;
};

// TEST_F(EventWTest, IsLargeEvent) {
//     for (auto small_event : small_events_) {
//         EXPECT_FALSE(small_event.isLargeEvent());
//     }

//     for (auto large_event : large_events_) {
//         EXPECT_TRUE(large_event.isLargeEvent());
//     }
// }
