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
 * Sorts lines of c-style string by the beginning of each line, ignoring whitespaces, punctuation marks and case
 *
 * @param data[in] C-style string the lines of which should be sorted
 *
 * @return C-style string which is a set of sorted lines of original string
 */
const appChar* sortByStart(const appChar* data);

/**
 * Sorts lines of c-style string by the beginning of each reversed line, ignoring whitespaces, punctuation marks and case
 *
 * @param data[in] C-style string the lines of which should be sorted
 *
 * @return C-style string which is a set of sorted lines of original string
 */
const appChar* sortByEnd(const appChar* data);

#endif //ISP_DZ2_POEM_SORTER_H
