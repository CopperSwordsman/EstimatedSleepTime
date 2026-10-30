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

bool Heap::isEmpty() const {return heapData.empty();}

const InfoNode* Heap::top() const {
    if (isEmpty()) {
        std::cerr << "Heap is empty" << std::endl;
        return nullptr;
    }
    return heapData[0];
}