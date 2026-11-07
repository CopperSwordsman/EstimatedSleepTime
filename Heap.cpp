//
// Created by ericl on 10/26/2026.
//

#include "Heap.h"
#include <iostream>

Heap::Heap(const std::function<bool(const InfoNode&, const InfoNode&)>& compare) : compare(compare) {}

void Heap::push(InfoNode node) {
    heapData.push_back(node);
    siftUp(heapData.size() - 1);
}

void Heap::siftUp(int index) {
    while (index > 0) {
        int parent_index = (index - 1) / 2;

        // If child has more priority than parent, swap
        if (compare(heapData[index], heapData[parent_index])) {
            std::swap(heapData[index], heapData[parent_index]);
            index = parent_index;
        } else {
            break;
        }
    }
}

void Heap::siftDown(int index) {
    int child_index = (index * 2) + 1;
    while (child_index < heapData.size()) {
        // If right child index exists AND right has more priority than left, use right child index
        if (child_index + 1 < heapData.size() && compare(heapData[child_index + 1], heapData[child_index])) {
            child_index++;
        }

        // If child has more priority than parent, swap and update index
        if (compare(heapData[child_index], heapData[index])) {
            std::swap(heapData[child_index], heapData[index]);
            index = child_index;
        } else {
            break;
        }
        child_index = (index * 2) + 1;
    }
}

bool Heap::isEmpty() const {return heapData.empty();}

const InfoNode& Heap::top() const {
    if (isEmpty()) {
        std::cerr << "Heap is empty" << std::endl;
    }
    return heapData[0];
}

const std::vector<InfoNode>& Heap::getHeapData() const {return heapData;}

InfoNode Heap::extract() {
    if (isEmpty()) {
        std::cerr << "Heap is empty" << std::endl;
    }

    InfoNode node = heapData[0];
    heapData[0] = heapData[heapData.size() - 1];
    heapData.pop_back();
    siftDown(0);
    return node;
}

double Heap::getAvgValue(int metric, int start, int end) const {
    int size = 0;

    if (metric == static_cast<int>(InfoNodeType::sleepDuration)) {
        double duration_total = 0.00;
        for (const auto& node : heapData) {
            if (node.sleepQuality <= end && node.sleepQuality >= start) {
                duration_total += node.sleepDuration;
                size++;
            }
        }
        return duration_total / size;
    }
    if (metric == static_cast<int>(InfoNodeType::sleepLatency)) {
        double latency_total = 0.00;
        for (const auto& node : heapData) {
            if (node.sleepQuality <= end && node.sleepQuality >= start) {
                latency_total += node.sleepLatency;
                size++;
            }
        }
        return latency_total / size;
    }
    if (metric == static_cast<int>(InfoNodeType::stressScore)) {
        double stress_total = 0.00;
        for (const auto& node : heapData) {
            if (node.sleepQuality <= end && node.sleepQuality >= start) {
                stress_total += node.stressScore;
                size++;
            }
        }
        return stress_total / size;
    }
    if (metric == static_cast<int>(InfoNodeType::workHours)) {
        double work_total = 0.00;
        for (const auto& node : heapData) {
            if (node.sleepQuality <= end && node.sleepQuality >= start) {
                work_total += node.workHours;
                size++;
            }
        }
        return work_total / size;
    }
    if (metric == static_cast<int>(InfoNodeType::caffeineMg)) {
        double caffeine_total = 0.00;
        for (const auto& node : heapData) {
            if (node.sleepQuality <= end && node.sleepQuality >= start) {
                caffeine_total += node.caffeineMg;
                size++;
            }
        }
        return caffeine_total / size;
    }
    if (metric == static_cast<int>(InfoNodeType::screenTime)) {
        double screen_total = 0;
        for (const auto& node : heapData) {
            if (node.sleepQuality <= end && node.sleepQuality >= start) {
                screen_total += node.screenTime;
                size++;
            }
        }
        return screen_total / size;
    }
    return -1;
}