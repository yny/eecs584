#include <iostream>
#include "RoutingTree.h"
#include "RoutingTree.cpp"
#include "Node.cpp"

template <class T >
int checkRange(Range<T> range, Node<T> *node, Node<T> **subNode) {
	vector<Node<T> *> childNodes = node->getChildNodes();
	if (childNodes.size() == 0) {
		return 2;
	}
	
	for (int i = 0; i < childNodes.size() && !range.atRight(childNodes[i]->getRange()); i++) {
		if (range.overlap(childNodes[i]->getRange())) {
			if (range.contains(childNodes[i]->getRange()) && range.isContainedBy(childNodes[i]->getRange())) {
				return 1;
			}
			if (range.isContainedBy(childNodes[i]->getRange())) {
				*subNode = childNodes[i];
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
		std::cout<<"-1"<<std::endl;
		return;
	}
	
	Node<T> *node = RT->getRoot();
	while (1) {
		Node<T> *subNode = NULL;
		switch (checkRange(range, node, &subNode))
		{
		//contained in a subRange
			case 0:
			node = subNode;
			std::cout<<"0"<<std::endl;
			break;
		//exactly the same as a subRange
			case 1:
			*parentNode = node;
			std::cout<<"1"<<std::endl;
			return;
		//no overlap with an subRange
			case 2:
			*parentNode = node;
			std::cout<<"2"<<std::endl;
			return;
		//overlap with more than one subRange
			default:
			*parentNode = node;
			std::cout<<"3"<<std::endl;
			return;
		}
	}
} // -> return result node

void testNewRoot1() {
	Range<int> range1(1, 5);
	Node<int> *node = new Node<int>(range1);
	RoutingTree<int> *RT= new RoutingTree<int>(node);
	Range<int> range2(8, 10);
	Node<int> *parentNode;
	getShardIDs(RT, range2, &parentNode);
	parentNode->getRange().print();
}

void testNewRoot2() {
	Range<int> range1(1, 5);
	Node<int> *node = new Node<int>(range1);
	RoutingTree<int> *RT= new RoutingTree<int>(node);
	Range<int> range2(3, 10);
	Node<int> *parentNode;
	getShardIDs(RT, range2, &parentNode);
	parentNode->getRange().print();
}

void test() {
	Range<int> range1(1, 10);
	Node<int> *node1 = new Node<int>(range1);
	RoutingTree<int> *RT= new RoutingTree<int>(node1);
	Range<int> range2(1, 5);
	Node<int> *node2 = new Node<int>(range2);
	RT->getRoot()->insertChildNode(node2);
	
	Node<int> *parentNode;
	
	Range<int> range3(2, 3);
	Node<int> *node3 = new Node<int>(range3);
	getShardIDs(RT, range3, &parentNode);
	parentNode->insertChildNode(node3);
	parentNode->getRange().print();
	parentNode->printChildNodes();
	
	Range<int> range4(7, 8);
	Node<int> *node4 = new Node<int>(range4);
	getShardIDs(RT, range4, &parentNode);
	parentNode->insertChildNode(node4);
	parentNode->getRange().print();
	parentNode->printChildNodes();
	
	Range<int> range5(5, 6);
	Node<int> *node5 = new Node<int>(range5);
	getShardIDs(RT, range5, &parentNode);
	parentNode->insertChildNode(node5);
	parentNode->getRange().print();
	parentNode->printChildNodes();
	
	Range<int> range6(2, 9);
	getShardIDs(RT, range6, &parentNode);
	parentNode->getRange().print();
	
	getShardIDs(RT, range2, &parentNode);
	parentNode->getRange().print();
}

int main() {
	//testNewRoot1();
	//testNewRoot2();
	test();
	return 0;
}
