//
// Created by ericl on 10/26/2026.
//

#include "Heap.h"

Heap::Heap(const std::function<bool(const InfoNode *, const InfoNode *)>& compare) : compare(compare) {}

bool Heap::isEmpty() const {return heapData.empty();}