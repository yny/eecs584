#ifndef ROUTINGTREE_H
#define ROUTINGTREE_H

#include <iostream>
#include <vector>
#include "Range.h"
#include "Node.h"

template <class T>
class RoutingTree {
public:
    RoutingTree(Node<T> *root);
    Node<T> *getRoot(){return root;}
    void setRoot(Node<T> *node){root = node;}
    vector<Node<T> *> getShardIDs(Range<T> range, Node<T> **parentNode); // -> return result node

private:
    Node<T> *root;
    //Node<T> *search(Range<T> range); // -> return pointer of Parent Node
    vector<Range<T> > splitRange(Range<T> range, Node<T> *parentNode);
    vector<Node<T> *> insert(vector<Range<T> > subRanges, Node<T> *parentNode);
    int checkRange(Range<T> range, Node<T> *node, Node<T> *subNode);
};

class AdaptiveRouting {
    //map<Field *field, RoutingTree *tree> fieldToTreeMap;
};

#endif
