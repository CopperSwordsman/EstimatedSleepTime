//
// Created by thedi on 10/29/2026.
//
#ifndef ESTIMATEDSLEEPTIME_MAPS_H
#define ESTIMATEDSLEEPTIME_MAPS_H
#include <vector>
#include "infonode.h"
enum class Color {
    Red,
    Black
};
class RBNode {
    //what does a red and black node need lets think
    //color: a left right, a value and that value will be a vector with tuples?
    //maybe the tuples is too much though and too hard to gather from how about just the individual values in the object
    //so we could do sleep quality as the key and then have values that contribute to sleep quality under that
public:
    //sleepQuality is the value
    int sleepQuality;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    std::vector<InfoNode> nodes;
    void addNode(InfoNode node);
    double averageValue(int which);
    RBNode(int sleepQuality_);
};
class RBTree {
    RBNode* root;
    RBNode* NIL;

    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);
    void insertCorrection(RBNode* k);
public:
    RBTree();
    RBNode* getNode(int sleepQuality);
};
class CustomMap {
    RBTree tree;

public:
    RBNode& operator[](int sleepQuality_);
    CustomMap();
};
#endif //ESTIMATEDSLEEPTIME_MAPS_H