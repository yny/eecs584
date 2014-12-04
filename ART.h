#ifndef ART_H
#define ART_H

#include <iostream>
#include <vector>
#include "Range.h"

struct Cmp {
    bool operator() (const Node& node1, const Node& node2) const {
        if node1.getRange().overLap(node2.getRange()){
            throw "ERROR: Two ranges have overlap. Failed to compare!\n";
        }
        return node1.getRange().atLeft(node2.getRange());
    }
};

template <class T>
class Node {
public:
    Node(Range range){};
    Range getRange(){};
    vector<int> getShards(){};
    void setShards(vector<int> shards){};
    static bool canMerge(Node *node1, Node *node2){};
    void insert(Node *node){};
    void merge(Node *node1, Node *node2){};

private:
    Range range;
    vector<int> shardID;
    set<Node *, Cmp> subRange;
};

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