#include <iostream>
#include "RoutingTree.h"
#include "RoutingTree.cpp"
#include "Node.cpp"

template <class T >
int checkRange(Range<T> range, Node<T> *node, Node<T> *subNode) {
	vector<Node<T> *> childNodes = node->getChildNodes();
	if (childNodes.size() == 0) {
		return 2;
	}
	
	for (int i = 0; i != childNodes.size() && !range.atRight(childNodes[i]->getRange()); i++) {
		if (range.overlap(childNodes[i]->getRange())) {
			if (range.contains(childNodes[i]->getRange()) && range.isContainedBy(childNodes[i]->getRange())) {
				return 1;
			}
			if (range.contains(childNodes[i]->getRange())) {
				subNode = childNodes[i];
				return 0;
			}
			return 3;
		}
	}
	return 2;
}

template <class T >
void getShardIDs(RoutingTree<T> *RT, Range<T> range, Node<T> **parentNode){
	//range not contained in the root
	if (!RT->getRoot()->getRange().contains(range)) {
		//create a new root
		Range<T> newRange = RT->getRoot()->getRange().merge(range);
		Node<T> *newRoot = new Node<T>(newRange);
		newRoot->insertChildNode(RT->getRoot());
		RT->setRoot(newRoot);
		*parentNode = RT->getRoot();
		return;
	}
	
	Node<T> *node = RT->getRoot();
	while (1) {
		Node<T> *subNode = NULL;
		switch (checkRange(range, node, subNode))
		{
		//contained in a subRange
			case '0':
			node = subNode;
			break;
		//exactly the same as a subRange
			case '1':
			*parentNode = node;
			return;
		//no overlap with an subRange
			case '2':
			*parentNode = node;
			return;
		//overlap with more than one subRange
			default:
			*parentNode = node;
			return;
		}
	}
} // -> return result node

void test() {
	Range<int> range1(2, 4);
	Node<int> *node = new Node<int>(range1);
	RoutingTree<int> *RT= new RoutingTree<int>(node);
	Range<int> range2(1, 5);
	Node<int> *parentNode;
	getShardIDs(RT, range2, &parentNode);
	parentNode->getRange().print();
}

int main() {
	test();
	return 0;
}
