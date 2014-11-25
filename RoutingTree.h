#ifndef ROUTINGTREE_H
#define ROUTINGTREE_H

#include <iostream>
#include <vector>
#include "Range.h"
#include "Node.h"

class RoutingTree {
public:
    RoutingTree(Node *root);
    vector<Node *> getShardIDs(Range range, Node *parentNode); // -> return result node

private:
    Node *root;
    Node *search(Range range); // -> return pointer of Parent Node
    vector<Range> splitRange(Range range, Node *parentNode);
    vector<Node *> insert(vector<Range> subRanges, Node *parentNode);
};

class AdaptiveRouting {
    map<Field *field, RoutingTree *tree> fieldToTreeMap;
};

#endif
