/**
 * @file
 *
 * @brief Functions to sort poems
 */

#ifndef ISP_DZ2_POEM_SORTER_H
#define ISP_DZ2_POEM_SORTER_H

#include "app_common.h"
#include "my_sorts.h"

struct LineData {
    const appChar* start;
    const appChar* end;

    LineData(const appChar* start, const appChar* end):start(start), end(end) {}

    [[nodiscard]] size_t size() const {
        return end - start;
    }

    [[nodiscard]] bool empty() const {
        return size() == 0;
    }

    const appChar& operator[](size_t pos) const {
        if (pos >= size())
            throw std::out_of_range("pos " + std::to_string(pos) + " is out of range 0.." + std::to_string(size()));

        return start[pos];
    }
};

/**
 * Sorts lines of c-style string by the beginning of each line, ignoring whitespaces, punctuation marks and case
 *
 * @param data[in] C-style string the lines of which should be sorted
 *
 * @return C-style string which is a set of sorted lines of original string
 */
void sortByStart(std::vector<LineData>& data);

/**
 * Sorts lines of c-style string by the beginning of each reversed line, ignoring whitespaces, punctuation marks and case
 *
 * @param data[in] C-style string the lines of which should be sorted
 *
 * @return C-style string which is a set of sorted lines of original string
 */
void sortByEnd(std::vector<LineData>& data);

void fromCString(const appChar* str, size_t strLen, std::vector<LineData>& data);

#endif //ISP_DZ2_POEM_SORTER_H
