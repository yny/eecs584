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
    vector<T> getShards();
    void setShards(vector<T> shards);
    vector<Node<T> *> getChildNodes(){return childNodes;}
    void insertChildNode(Node<T> *node);

    //For test only
    void printChildNodes();

private:
    Range<T> range;
    vector<T> shardID;
    vector<Node<T> *> childNodes;
};

#endif
