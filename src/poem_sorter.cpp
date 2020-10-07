//
// Created by arti1208 on 02.10.2020.
//

#include <vector>
#include <functional>
#include <codecvt>
#include "my_sorts.h"
#include "poem_sorter.h"

static bool shouldSkipChar(const appChar& c) {
    return isspace(c) || ispunct(c);
}

void sortByStart(std::vector<LineData>& data) {
    std::function<int(const LineData&, const LineData&)> comparator = [](const LineData& str, const LineData& other) {

        size_t firstPos = 0;
        for (; firstPos < str.length() && shouldSkipChar(str[firstPos]); ++firstPos);

        size_t secondPos = 0;
        for (; secondPos < other.length() && shouldSkipChar(other[secondPos]); ++secondPos);

        for (; firstPos < str.length() && secondPos < other.length(); ++firstPos, ++secondPos) {

            const appChar& firstChar = std::tolower(str[firstPos]);
            const appChar& secondChar = std::tolower(other[secondPos]);

            if (firstChar != secondChar) {
                return ((firstChar < secondChar) && !shouldSkipChar(secondChar)) || shouldSkipChar(firstChar) ? -1 : 1;
            }
        }

        if (str.length() < other.length()) return -1;
        else if (str.length() == other.length()) return 0;
        else return 1;
    };

    quick_sort::sort(data, comparator);
}

void sortByEnd(std::vector<LineData>& data) {
    std::function<int(const LineData&, const LineData&)> comparator = [](const LineData& str, const LineData& other) {
        ssize_t firstPos = str.length() - 1;
        for (; firstPos >= 0 && shouldSkipChar(str[firstPos]); --firstPos);

        ssize_t secondPos = other.length() - 1;
        for (; secondPos >= 0 && shouldSkipChar(other[secondPos]); --secondPos);

        for (; firstPos >= 0 && secondPos >= 0; --firstPos, --secondPos) {

            const appChar& firstChar = std::tolower(str[firstPos]);
            const appChar& secondChar = std::tolower(other[secondPos]);

            if (firstChar != secondChar) {
                return ((firstChar < secondChar) && !shouldSkipChar(secondChar)) || shouldSkipChar(firstChar) ? -1 : 1;
            }
        }

        if (str.length() < other.length()) return -1;
        else if (str.length() == other.length()) return 0;
        else return 1;
    };

    quick_sort::sort(data, comparator);
}

void fromCString(const appChar* str, size_t strLen, std::vector<LineData>& data) {
    size_t start = 0;
    for (size_t i = 0; i < strLen; ++i) {
        if (str[i] == '\n') {
            data.emplace_back(str + start, str + i);

            start = i + 1;
        }
    }
    if (start + 1 < strLen) {
        data.emplace_back(str + start, str + strLen - 1);
    }
}
