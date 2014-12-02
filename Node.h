#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include "Range.h"

using namespace std;

/*struct Cmp {
    bool operator() (const Node& node1, const Node& node2) const {
        if (node1.getRange().overLap(node2.getRange)){
            throw "ERROR: Two ranges have overlap. Failed to compare!\n";
        }
        return node1.getRange().atLeft(node2.getRange());
    }
};*/

template <class T>
class Node {
public:
    Node(Range<T> range);
    Range<T> getRange();
    vector<int> getShards();
    vector<Node *> getChildNodes();
    void setShards(vector<int> shards);
    static bool canMerge(Node *node1, Node *node2);
    void insertChildNode(Node *node);
    void merge(Node *node1, Node *node2);

    //For test only
    void printChildNodes();

private:
    Range<T> range;
    vector<int> shardID;
    vector<Node *> childNodes;
};

#endif
