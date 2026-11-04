//
// Created by ericl on 10/26/2026.
//

#ifndef ESTIMATEDSLEEPTIME_HEAP_H
#define ESTIMATEDSLEEPTIME_HEAP_H
#include <functional>
#include <vector>
#include "infonode.h"

class Heap {
private:
    std::function<bool(const InfoNode&, const InfoNode&)> compare; // comparator for min/max heap
    std::vector<InfoNode> heapData;
public:
    Heap() = default;
    explicit Heap(const std::function<bool(const InfoNode&, const InfoNode&)>& compare);
    void push(InfoNode node);
    void siftUp(int index);
    void siftDown(int index);
    bool isEmpty() const;
    const InfoNode& top() const;
    const std::vector<InfoNode>& getHeapData() const;
    InfoNode extract();
    double get_avg_value(int metric, int start, int end) const;
};
#endif //ESTIMATEDSLEEPTIME_HEAP_H