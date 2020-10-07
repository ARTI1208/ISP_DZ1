#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by arti1208 on 02.10.2020.
//

#include "gtest/gtest.h"
#include "../src/my_sorts.h"
#include "../src/poem_sorter.h"

TEST(HamletSortSuite, QuickSortAscendingTest) {
    std::vector<int> v({1, 2, 3, 49, 12, 3, 9, 34});

    std::function<int(const int&, const int&)> intAscendingComparator = [](const int& fst, const int& scd) {
        if (fst < scd) return -1;
        else if (fst == scd) return 0;
        return 1;
    };

    quick_sort::sort(v, intAscendingComparator);

    for (size_t i = 1; i < v.size(); ++i) {
        ASSERT_LE(v[i - 1], v[i]);
    }
}

TEST(HamletSortSuite, QuickSortDescendingTest) {
    std::vector<int> v({1, 2, 3, 49, 12, 3, 9, 34});

    std::function<int(const int&, const int&)> intDescendingComparator = [](const int& fst, const int& scd) {
        if (fst < scd) return 1;
        else if (fst == scd) return 0;
        return -1;
    };

    quick_sort::sort(v, intDescendingComparator);

    for (size_t i = 1; i < v.size(); ++i) {
        ASSERT_GE(v[i - 1], v[i]);
    }
}

TEST(HamletSortSuite, QuickSortStringTest) {
    std::vector<std::string> v({"Hello", "hello", "ha-ha-ha", "hi"});

    std::function<int(const std::string&, const std::string&)> stringAscendingComparator = [](const std::string& fst, const std::string& scd) {
        return fst.compare(scd);
    };

    quick_sort::sort(v, stringAscendingComparator);

    for (size_t i = 1; i < v.size(); ++i) {
        ASSERT_TRUE(v[i - 1] < v[i]);
    }

    ASSERT_STREQ(v[0].c_str(), "Hello");
    ASSERT_STREQ(v[1].c_str(), "ha-ha-ha");
    ASSERT_STREQ(v[2].c_str(), "hello");
    ASSERT_STREQ(v[3].c_str(), "hi");
}

TEST(HamletSortSuite, LinesFromString) {

    const appChar* string = "  HelloMan\nhello\n\tha-ha-ha\n!hi";

    std::vector<LineData> v;
    fromCString(string, strlen(string) , v);

    ASSERT_EQ(v.size(), 4);

    const appChar* stringEnd = string + strlen(string) - 1;

    const appChar* helloManStart = string;
    const appChar* helloManEnd = std::find(string, stringEnd + 1, '\n');

    const appChar* helloStart = helloManEnd + 1;
    const appChar* helloEnd = std::find(helloManEnd + 1, stringEnd + 1, '\n');

    const appChar* hahaStart = helloEnd + 1;
    const appChar* hahaEnd = std::find(helloEnd + 1, stringEnd + 1, '\n');

    const appChar* hiStart = hahaEnd + 1;
    const appChar* hiEnd = stringEnd;

    ASSERT_EQ(helloManStart, v[0].start);
    ASSERT_EQ(helloManEnd,   v[0].end);
    ASSERT_EQ(helloStart,    v[1].start);
    ASSERT_EQ(helloEnd,      v[1].end);
    ASSERT_EQ(hahaStart,     v[2].start);
    ASSERT_EQ(hahaEnd,       v[2].end);
    ASSERT_EQ(hiStart,       v[3].start);
    ASSERT_EQ(hiEnd,         v[3].end);

    ASSERT_EQ(11,         v[0].length());
    ASSERT_EQ(6,          v[1].length());
    ASSERT_EQ(10,         v[2].length());
    ASSERT_EQ(3,          v[3].length());
}

TEST(HamletSortSuite, PoemSortByStartTest) {

    const appChar* string = "  HelloMan\nhello\n\tha-ha-ha\n!hi";

    std::vector<LineData> v;
    fromCString(string, strlen(string) , v);

    sortByStart(v);

    ASSERT_EQ(v.size(), 4);

    const appChar* stringEnd = string + strlen(string) - 1;

    const appChar* helloManStart = string;
    const appChar* helloManEnd = std::find(string, stringEnd + 1, '\n');

    const appChar* helloStart = helloManEnd + 1;
    const appChar* helloEnd = std::find(helloManEnd + 1, stringEnd + 1, '\n');

    const appChar* hahaStart = helloEnd + 1;
    const appChar* hahaEnd = std::find(helloEnd + 1, stringEnd + 1, '\n');

    const appChar* hiStart = hahaEnd + 1;
    const appChar* hiEnd = stringEnd;


    ASSERT_EQ(hahaStart,     v[0].start);
    ASSERT_EQ(hahaEnd,       v[0].end);
    ASSERT_EQ(helloStart,    v[1].start);
    ASSERT_EQ(helloEnd,      v[1].end);
    ASSERT_EQ(helloManStart, v[2].start);
    ASSERT_EQ(helloManEnd,   v[2].end);
    ASSERT_EQ(hiStart,       v[3].start);
    ASSERT_EQ(hiEnd,         v[3].end);
}

TEST(HamletSortSuite, PoemSortByEndTest) {

    const appChar* string = "  HelloMan\nhello\n\tha-ha-ha\n!hi";

    std::vector<LineData> v;
    fromCString(string, strlen(string) , v);

    sortByEnd(v);

    ASSERT_EQ(v.size(), 4);

    const appChar* stringEnd = string + strlen(string) - 1;

    const appChar* helloManStart = string;
    const appChar* helloManEnd = std::find(string, stringEnd + 1, '\n');

    const appChar* helloStart = helloManEnd + 1;
    const appChar* helloEnd = std::find(helloManEnd + 1, stringEnd + 1, '\n');

    const appChar* hahaStart = helloEnd + 1;
    const appChar* hahaEnd = std::find(helloEnd + 1, stringEnd + 1, '\n');

    const appChar* hiStart = hahaEnd + 1;
    const appChar* hiEnd = stringEnd;

    ASSERT_EQ(hahaStart,     v[0].start);
    ASSERT_EQ(hahaEnd,       v[0].end);
    ASSERT_EQ(hiStart,       v[1].start);
    ASSERT_EQ(hiEnd,         v[1].end);
    ASSERT_EQ(helloManStart, v[2].start);
    ASSERT_EQ(helloManEnd,   v[2].end);
    ASSERT_EQ(helloStart,    v[3].start);
    ASSERT_EQ(helloEnd,      v[3].end);
}

TEST(HamletSortSuite, LineDataTest) {
    LineData line1((appChar *) 1, (appChar *) 5);
    ASSERT_EQ(line1.length(), 5);


    LineData line2((appChar *) 1, (appChar *) 1);
    ASSERT_EQ(line2.length(), 1);
    ASSERT_THROW(line2[10], std::out_of_range);
    ASSERT_THROW(line2[-10], std::out_of_range);

    ASSERT_THROW(LineData((appChar *) 2, (appChar *) 1), std::invalid_argument);
    ASSERT_THROW(LineData(nullptr, (appChar *) 1), std::invalid_argument);
    ASSERT_THROW(LineData((appChar *) 2, nullptr), std::invalid_argument);

    const appChar* testString = "test";

    LineData testLine(testString, testString + strlen(testString) - 1);

    ASSERT_EQ(testLine.length(), 4);
    ASSERT_EQ(testLine[0], 't');
    ASSERT_EQ(testLine[1], 'e');
    ASSERT_EQ(testLine[2], 's');
    ASSERT_EQ(testLine[3], 't');
}
#pragma clang diagnostic pop // yeah, CLion bug