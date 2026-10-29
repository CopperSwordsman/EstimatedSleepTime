//
// Created by thedi on 10/29/2026.
//

#include "maps.h"
RBNode::RBNode(int sleepQuality_) {
    sleepQuality = sleepQuality_;
    color = Color::Red;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
void RBNode::addNode(InfoNode info_node) {
   nodes.push_back(info_node);
}
double RBNode::averageValue(int which) {
    double size = static_cast<int>(nodes.size());
    if (which == static_cast<int>(InfoNodeType::sleepDuration)) {
        int durationTotal = 0;
        for (int i = 0; i<size;i++) {
            durationTotal += nodes[i].sleepDuration;
        }
        return static_cast<int>(durationTotal / size);
    }
    if (which == static_cast<int>(InfoNodeType::sleepLatency)) {
        int latencyTotal = 0;
        for (int i = 0; i<size;i++) {
            latencyTotal+= nodes[i].sleepLatency;
        }
        return static_cast<int>(latencyTotal/size);
    }
    if (which == static_cast<int>(InfoNodeType::stressScore)) {
        double stressTotal = 0;
        for (int i = 0; i<nodes.size();i++) {
            stressTotal += nodes[i].stressScore;
        }
        return stressTotal/size;
    }
    if (which == static_cast<int>(InfoNodeType::workHours)) {
        double workTotal = 0;
        for (int i = 0; i<nodes.size();i++) {
            workTotal += nodes[i].workHours;
        }
        return workTotal/size;
    }
    if (which == static_cast<int>(InfoNodeType::caffeineMg)) {
        double caffeineTotal = 0;
        for (int i = 0; i<nodes.size();i++) {
            caffeineTotal += nodes[i].caffeineMg;
        }
        return caffeineTotal/size;
    }
    if (which == static_cast<int>(InfoNodeType::screenTime)) {
        double screenTotal = 0;
        for (int i = 0; i<nodes.size();i++) {
            screenTotal += nodes[i].screenTime;
        }
        return screenTotal/size;
    }
    return -1;
}
void RBTree::leftRotate(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;

    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
void RBTree::rightRotate(RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;

    if (y->right != NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}
void RBTree::insertCorrection(RBNode* k) {
    //we just traverse the loop and either do a simple color swap and rotate or double rotate
    while (k!= root && k->parent->color == Color::Red) {
        if (k->parent == k->parent->parent->left) {
            RBNode* uncle = k->parent->parent->left;
            if (uncle->color == Color::Red) {
                k->parent->color = Color::Black;
                uncle->color = Color::Black;
                k->parent->parent->color = Color::Red;
                k=k->parent->parent;
            }
            else {
                if (k==k->parent->right) {
                    k=k->parent;
                    leftRotate(k);
                }
                k->parent->color = Color::Black;
                k->parent->parent->color = Color::Red;
                rightRotate(k->parent->parent);
            }
        }
        else {
            // Mirror Case: Parent is the right child
            RBNode* uncle = k->parent->parent->left;

            if (uncle->color == Color::Red) {
                k->parent->color = Color::Black;
                uncle->color = Color::Black;;
                k->parent->parent->color = Color::Red;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = Color::Black;;
                k->parent->parent->color = Color::Red;
                leftRotate(k->parent->parent);
            }
        }
    }
    root->color = Color::Black;
}
RBNode* RBTree::getNode(int sleepQuality) {
    RBNode* node = new RBNode(sleepQuality);
    node->left = NIL;
    node->right = NIL;
    RBNode* parent = nullptr;
    RBNode* current = root;
    while (current != NIL) {
        parent = current;
        if (node->sleepQuality < current->sleepQuality) {
            current = current->left;
        }
        else if (node->sleepQuality > current->sleepQuality) {
            current = current->right;
        }
        else {
            //this is where we just have an existing node and we have literally no reason to change RB properties cause nothing actually changed
            //returning here is fine and we've deleted the node we made cause that was useless
            delete node;
            return current;
        }
    }
    node->parent = parent;
    if (parent == nullptr) {
        root = node;
    }
    else if (node->sleepQuality < parent->sleepQuality) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }
    //this is the first case where we just added to the root so we gotta make it black
    if (node->parent == nullptr) {
        node->color = Color::Black;
        return node;
    }
    //different case where we added a red node to under the root node, these don't hurt the tree at all
    if (node->parent->parent == nullptr) {
        return node;
    }
    insertCorrection(node);
    return node;
}
RBTree::RBTree() {
    NIL = new RBNode(-1);
    NIL->color = Color::Black;
    NIL->left = nullptr;
    NIL->right = nullptr;
    NIL->parent = nullptr;
    root = NIL;
}
//cases: tree[1] = 5
//int x = tree[1]
RBNode& CustomMap::operator[](int sleepQuality_) {
    //all we want this to do is return a reference to the RBNode if it exists, if it doesn't exist we can safely make a new node
    return *tree.getNode(sleepQuality_);

}
CustomMap::CustomMap() {}