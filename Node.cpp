#include "Node.h"

/* Node Class */
template <class T>
Node<T>::Node(Range<T> range){
    this->range = range;
}

template <class T>
Range<T> Node<T>::getRange(){
	return this->range;
}

template <class T>
vector<int> Node<T>::getShards(){
	return this->shardID;
}

template <class T>
void Node<T>::setShards(vector<int> shards){
	this->shardID = shards;
}

template <class T>
bool Node<T>::canMerge(Node *node1, Node *node2){

}

template <class T>
void Node<T>::insertChildNode(Node *node){
	int i = 0;
	int j = 0;
	bool insert_flag = false;
	Range<T> range = node->getRange();

	if (childNodes.size() == 0){
		this->childNodes.push_back(node);
		return;
	}

	vector<Node *> newChildNodes(this->childNodes.size() + 1);
	for (; i < this->childNodes.size(); j++){
		Range<T> curRange = this->childNodes[i]->getRange();
		if (range.overlap(curRange)){
			cerr << "ERROR: Ranges have overlap!\n";
		}
		if (range.atLeft(curRange) && !insert_flag){
			newChildNodes[j] = node;
			insert_flag = true;
			cout<<"flag set"<<endl;
		}
		else{
			newChildNodes[j] = this->childNodes[i];
			i++;
		}
	}

	if (!insert_flag){
		newChildNodes[j] = node;
	}
	
	this->childNodes = newChildNodes;
}

template <class T>
void Node<T>::merge(Node<T> *node1, Node<T> *node2){

}

template <class T>
void Node<T>::printChildNodes(){
	cout<<"size: "<<this->childNodes.size()<<endl;
	for (int i = 0; i < this->childNodes.size(); i ++){
		//this->childNodes[i]->getRange();
		this->childNodes[i]->getRange().print();
	}
}
