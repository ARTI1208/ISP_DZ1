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

TEST(HamletSortSuite, PoemSortByStartTest) {

    std::vector<std::string> v({"  HelloMan", "hello", "\tha-ha-ha", "!hi"});

//    sortByStart(v);

    ASSERT_STREQ(v[0].c_str(), "\tha-ha-ha");
    ASSERT_STREQ(v[1].c_str(), "hello");
    ASSERT_STREQ(v[2].c_str(), "  HelloMan");
    ASSERT_STREQ(v[3].c_str(), "!hi");
}