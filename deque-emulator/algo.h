//
// Created by Kirill "Raaveinm" on 11/2/25.
//

#ifndef DEQUEUE_EMULATOR_ALGO_H
#define DEQUEUE_EMULATOR_ALGO_H

#include <deque>

template<class T, class Comp>
static std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> res;
    auto it1 = half1.begin();
    auto it2 = half2.begin();

    while (it1 != half1.end() && it2 != half2.end()) {
        if (comparator(*it1, *it2)) {
            res.push_back(*it1);
            ++it1;
        } else {
            res.push_back(*it2);
            ++it2;
        }
    }

    res.insert(res.end(), it1, half1.end());
    res.insert(res.end(), it2, half2.end());

    return res;
}


template<class T, class Comp>
static std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1)
        return src;

    const size_t mid = src.size() / 2;

    const std::deque<T> left_sorted = MergeSort(std::deque<T>{src.begin(), src.begin() + mid}, comparator);
    const std::deque<T> right_sorted = MergeSort(std::deque<T>{src.begin() + mid, src.end()}, comparator);

    return Merge(left_sorted, right_sorted, comparator);
}

#endif //DEQUEUE_EMULATOR_ALGO_H