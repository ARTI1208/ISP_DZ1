/**
 * @file
 *
 * @brief Implementations of different sorting algorithms (currently only quick sort)
 */

#ifndef ISP_DZ2_MY_SORTS_H
#define ISP_DZ2_MY_SORTS_H

#include <vector>
#include <functional>
#include <iostream>

class quick_sort {

private:
    template<typename Elem>
    static size_t quickSortPartitioner(std::vector<Elem>& data, size_t from, size_t to,
                                                    const std::function<int(const Elem&, const Elem&)>& comparator) {
        size_t medium = (from + to) / 2;
        Elem pivot = data[medium];

        size_t i = from;
        size_t j = to;

        while (i <= j) {

            while (i <= j && comparator(data[i], pivot) < 0) {
                ++i;
            }

            while (i <= j && comparator(data[j], pivot) > 0) {
                --j;
            }

            if (i <= j) {
                std::swap(data[i], data[j]);
                ++i;
                --j;
            }

//            if (comparator(data[i], pivot) >= 0 && (comparator(data[j], pivot) <= 0)) {
//
//                std::swap(data[i], data[j]);
//                ++i;
//                --j;
//
//                if (i >= j) break;
//            }
//
//            while (comparator(data[i], pivot) < 0) {
//                ++i;
//            }
//
//            while (comparator(data[j], pivot) > 0) {
//                --j;
//            }
        }

//        if (j + 2 < i) {
//            std::cout << i << " vs " << j << "\n";
//        }

        return i;
    }

    template<typename Elem>
    static void sort2elems(Elem& firstElem, Elem& secondElem,
                           const std::function<int(const Elem&, const Elem&)>& comparator) {
        if (comparator(firstElem, secondElem) > 0) {
            std::swap(firstElem, secondElem);
        }
    }

    template<typename Elem>
    static void sort3elems(Elem& firstElem, Elem& secondElem, Elem& thirdElem,
                           const std::function<int(const Elem&, const Elem&)>& comparator) {
        if (comparator(firstElem, secondElem) > 0) {
            std::swap(firstElem, secondElem);
        }
        if (comparator(secondElem, thirdElem) > 0) {
            std::swap(secondElem, thirdElem);
        }
        if (comparator(firstElem, secondElem) > 0) {
            std::swap(firstElem, secondElem);
        }
    }

    template<typename Elem>
    static void quickSortImpl(std::vector<Elem>& data, size_t from, size_t to,
                       const std::function<int(const Elem&, const Elem&)>& comparator) {
        if (from < to) {

            switch (to - from) {
                case 1:
                    sort2elems(data[from], data[to], comparator);
                    return;
                case 2:
                    sort3elems(data[from], data[from + 1], data[from + 2], comparator);
                    return;
            }

            size_t p = quickSortPartitioner(data, from, to, comparator);

            if (from + 1 < p) {
                quickSortImpl(data, from, p - 1, comparator);
            }

            if (p < to) {
                quickSortImpl(data, p, to, comparator);
            }
        }
    }

public:

    /**
     * Sorts given vector in-place using the provided comparator to determine the relationship between objects
     *
     * @param data[in, out] Vector to sort
     * @param comparator[in] Function that compare vector elements. Should return negative value if first element is less
     * than second, zero if they are equal and positive value if the second argument is greater
     */
    template<typename Elem>
    static void sort(std::vector<Elem>& data, const std::function<int(const Elem&, const Elem&)>& comparator) {
        if (data.size() < 2) return;
        quickSortImpl(data, 0, data.size() - 1, comparator);
    }

};

#endif //ISP_DZ2_MY_SORTS_H
