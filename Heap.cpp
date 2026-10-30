//
// Created by ericl on 10/26/2026.
//

#include "Heap.h"
#include <iostream>

Heap::Heap(const std::function<bool(const InfoNode *, const InfoNode *)>& compare) : compare(compare) {}

Heap::~Heap() {
    for (const auto& node_ptr : heapData) {
        delete node_ptr;
    }
}

void Heap::push(InfoNode* node_ptr) {
    heapData.push_back(node_ptr);
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

const InfoNode* Heap::top() const {
    if (isEmpty()) {
        std::cerr << "Heap is empty" << std::endl;
        return nullptr;
    }
    return heapData[0];
}