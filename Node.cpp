#include "Node.h"

/* Node Class */
template <class T>
Node<T>::Node(Range<T> range){
    this->range = range;
}

template <class T>
Range<T> Node<T>::getRange(){

}

template <class T>
vector<int> Node<T>::getShards(){

}

template <class T>
void Node<T>::setShards(vector<int> shards){

}

template <class T>
bool Node<T>::canMerge(Node *node1, Node *node2){

}

template <class T>
void Node<T>::insert(Node *node){

}

template <class T>
void Node<T>::merge(Node<T> *node1, Node<T> *node2){

}
