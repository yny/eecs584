#ifndef ROUTINGTREE_H
#define ROUTINGTREE_H

#include <iostream>
#include <vector>
#include "Range.h"
#include "Node.h"

class RoutingTree {
public:
    RoutingTree(Node *root){};
    Node *search(Range range){};

private:
    Node *root;
    Range splitRange(Range range){};
    void insert(Range range){};
};

class AdaptiveRouting {
    map<Field *field, RoutingTree *tree> fieldToTreeMap;
};

#endif
