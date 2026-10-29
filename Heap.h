//
// Created by ericl on 10/26/2026.
//

#ifndef ESTIMATEDSLEEPTIME_HEAP_H
#define ESTIMATEDSLEEPTIME_HEAP_H
#include <functional>
#include <vector>

// can remove later for the node struct file
struct Node {
    int key;
    std::vector<std::tuple<int, int, double, double, double, double>> values;
};

class Heap {
private:
    std::function<bool(const Node*, const Node*)> compare; // comparator for min/max heap
    std::vector<Node*> heapData;
public:
    explicit Heap(std::function<bool(const Node*, const Node*)> compare);
    Heap(const Heap&) = delete; // don't use copy constructor
    Heap& operator=(const Heap&) = delete; // don't use copy assignment operator
    ~Heap();
    void push(Node* node_ptr);
    void siftUp(int index);
    void siftDown(int index);
    bool isEmpty() const;
    const Node* top() const;
    const Node* extract();
};
#endif //ESTIMATEDSLEEPTIME_HEAP_H