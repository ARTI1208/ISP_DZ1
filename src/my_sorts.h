//
// Created by arti1208 on 02.10.2020.
//

#ifndef ISP_DZ2_MY_SORTS_H
#define ISP_DZ2_MY_SORTS_H

#include <vector>
#include <functional>

class quick_sort {

private:
    template<typename Elem>
    static std::pair<int, int> quickSortPartitioner(std::vector<Elem>& data, int from, int to,
                                                    const std::function<int(const Elem&, const Elem&)>& comparator) {
        int medium = (from + to) / 2;
        Elem pivot = data[medium];

        int i = from;
        int j = to;

        while (i <= j) {

            if (comparator(data[i], pivot) >= 0 && (comparator(data[j], pivot) <= 0)) {

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
    static void quickSortImpl(std::vector<Elem>& data, int from, int to,
                       const std::function<int(const Elem&, const Elem&)>& comparator) {
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

public:
    template<typename Elem>
    static void sort(std::vector<Elem>& data, const std::function<int(const Elem&, const Elem&)>& comparator) {
        if (data.size() < 2) return;
        quickSortImpl(data, 0, data.size() - 1, comparator);
    }

};

#endif //ISP_DZ2_MY_SORTS_H