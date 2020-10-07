/**
 * @file
 *
 * @brief Functions to sort poems
 */

#ifndef ISP_DZ2_POEM_SORTER_H
#define ISP_DZ2_POEM_SORTER_H

#include "app_common.h"
#include "my_sorts.h"

/**
 * Structure that represents a line of text
 */
struct LineData {
    /**
     * Pointer to the beginning of line. Non-null
     */
    const appChar* start;

    /**
     * Pointer to the end of line (inclusive). Non-null
     */
    const appChar* end;

    /*!
     * Constructs th structure with given parameters. Line should contain at least one character
     *
     * @param start Pointer to the beginning of line
     * @param end Pointer to the end of line
     *
     * @throws invalid_argument if either start or end is nullptr, or if end is less than start
     */
    LineData(const appChar* start, const appChar* end) : start(start), end(end) {
        if (start == nullptr) throw std::invalid_argument("Start should not be null");
        if (end   == nullptr) throw std::invalid_argument("End should not be null");
        if (start > end)      throw std::invalid_argument("Start should be less than or equal to end");
    }

    /**
     * Returns the length of the line. Line contains at least one symbol
     *
     * @return The length of the line
     */
    [[nodiscard]] size_t length() const {
        return end - start + 1;
    }

    /**
     * Returns the char at given position
     *
     * @param pos Position of char to be returned
     *
     * @return Const reference to th char at given position
     *
     * @throws out_of_range if pos is equal to or exceeds the length of line
     */
    const appChar& operator[](size_t pos) const {
        if (pos >= length())
            throw std::out_of_range("pos " + std::to_string(pos) + " is out of range 0.." + std::to_string(length()));

        return start[pos];
    }
};

/**
 * Sorts lines (represented by instances of LineData) of text by the beginning of each line,
 * ignoring whitespaces, punctuation marks and case
 *
 * @param data[in,out] Vector that contains lines to be sorted
 */
void sortByStart(std::vector<LineData>& data);

/**
 * Sorts lines (represented by instances of LineData) of text by the beginning of each reversed line,
 * ignoring whitespaces, punctuation marks and case
 *
 * @param data[in,out] Vector that contains lines to be sorted
 */
void sortByEnd(std::vector<LineData>& data);

/**
 * Converts c-style string into vector of @see LineData instances
 *
 * @param appChar[in] C-style string that should be converted to LineData vector
 * @param strLen Length of the given string
 * @param data[out] Vector in which instances of LineData would be placed
 *
 * @return C-style string which is a set of sorted lines of original string
 */
void fromCString(const appChar* str, size_t strLen, std::vector<LineData>& data);

#endif //ISP_DZ2_POEM_SORTER_H
