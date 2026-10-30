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

bool Heap::isEmpty() const {return heapData.empty();}

const InfoNode* Heap::top() const {
    if (isEmpty()) {
        std::cerr << "Heap is empty" << std::endl;
        return nullptr;
    }
    return heapData[0];
}