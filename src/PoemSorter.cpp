//
// Created by arti1208 on 02.10.2020.
//

#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <functional>
#include "PoemSorter.h"

template<typename Elem>
static std::pair<int, int> quickSortPartitioner(std::vector<Elem>& data, int from, int to, const std::function<int(const Elem&, const Elem&)>& comparator) {
    int medium = (from + to) / 2;
    Elem pivot = data[medium];

    int i = from;
    int j = to;

    while (i <= j)
    {

        if (comparator(data[i], pivot) >= 0 && (comparator(data[j], pivot) <= 0))
        {

            std::swap(data[i], data[j]);
            ++i;
            --j;

            if (i >= j) break;
        }

        while (comparator(data[i], pivot) < 0) {
            ++i;
        }

        while (comparator(data[j], pivot) > 0) {
            --j;
        }
    }

    return {i, j};
}

template<typename Elem>
static void quickSortImpl(std::vector<Elem>& data, int from, int to, const std::function<int(const Elem&, const Elem&)>& comparator) {
    if (from < to) {
        std::pair<int, int> p = quickSortPartitioner(data, from, to, comparator);

        if (from < p.second) {
            quickSortImpl(data, from, p.second, comparator);
        }

        if (p.first < to) {
            quickSortImpl(data, p.first, to, comparator);
        }
    }
}

template<typename Elem>
static void quickSort(std::vector<Elem>& data, const std::function<int(const Elem&, const Elem&)>& comparator) {
    if (data.size() < 2) return;
    quickSortImpl(data, 0, data.size() - 1, comparator);
}

static bool shouldSkipChar(const appChar& c) {
    return ispunct(c) || isblank(c);
}

static appChar* splitAndSort(const appChar* data, const std::function<int(const appString&, const appString&)>& comparator) {
    appStringStream ss(data);
    appString item;
    std::vector<appString> elems;
    appChar delimiter = '\n';
    while (std::getline(ss, item, delimiter)) {
        elems.push_back(std::move(item));
    }

    quickSort(elems, comparator);

    appOutStringStream os;

    for (size_t i = 0; i < elems.size() - 1; ++i) {
        os << elems[i] << "\n";
    }

    os << elems[elems.size() - 1];

    appString res = os.str();
    auto* sorted = new appChar[res.size()];

    os.str().copy(sorted, res.size());

    return sorted;
}

const appChar* sortByStart(const appChar* data) {
    return splitAndSort(data, [](const appString& str, const appString& other) {

        size_t firstPos = 0;
        for (; firstPos < str.size() && shouldSkipChar(str[firstPos]); ++firstPos);

        size_t secondPos = 0;
        for (; secondPos < other.size() && shouldSkipChar(other[secondPos]); ++secondPos);

        for (size_t to = std::min(str.size() , other.size()); std::max(firstPos, secondPos) < to; ++firstPos, ++secondPos) {
            const appChar& firstChar = std::tolower(str[firstPos]);
            const appChar& secondChar = std::tolower(other[secondPos]);

            if (firstChar != secondChar) return firstChar < secondChar ? -1 : 1;
        }

        if (str.size() < other.size()) return -1;
        else if (str.size() == other.size()) return 0;
        else return 1;
    });
}

const appChar* sortByEnd(const appChar* data) {
    return splitAndSort(data, [](const appString& str, const appString& other) {
        if (str.empty()) return other.empty() ? 0 : -1;
        if (other.empty()) return 1;

        long firstPos = str.size() - 1;
        for (; firstPos >= 0 && shouldSkipChar(str[firstPos]); --firstPos);

        long secondPos = other.size() - 1;
        for (; secondPos >= 0 && shouldSkipChar(other[secondPos]); --secondPos);

        for (; std::min(firstPos, secondPos) >= 0; --firstPos, --secondPos) {
            const appChar& firstChar = std::tolower(str[firstPos]);
            const appChar& secondChar = std::tolower(other[secondPos]);

            if (firstChar != secondChar) return firstChar < secondChar ? -1 : 1;
        }

        if (str.size() < other.size()) return -1;
        else if (str.size() == other.size()) return 0;
        else return 1;
    });
}