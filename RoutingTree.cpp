#include "RoutingTree.h"

/* Routing Tree */
template <class T >
RoutingTree<T>::RoutingTree(Node<T> *root){
	this->root = new Node<T>(root->range);
}

template <class T >
vector<Node<T> *> RoutingTree<T>::getShardIDs(Range<T> range, Node<T> *parentNode){
	//range not contained in the root
	if (!range.overlap(root->range)) {
		//create a new root
		Range<T> newRange(range.first, range.second);
		Node<T> *newRoot = new Node<T>(newRange);
		newRoot->subRange.insert(root);
		root = newRoot;
		
		parentNode = root;
		return insert(vector<Range<T> >(1, range), root);
	}
	
	Node<T> *node = root;
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
			parentNode = node;
			return vector<Node<T> >(1, node);
		//no overlap with an subRange
			case '2':
			parentNode = node;
			return insert(vector<Range<T> >(1, range), node);
		//overlap with some subRanges
			default:
			parentNode = node;
			return insert(splitRange(range, node), node);
		}
	}
} // -> return result node

template <class T >
Node<T> *RoutingTree<T>::search(Range<T> range){
	
} // -> return pointer of Parent Node

template <class T >
vector<Range<T> > RoutingTree<T>::splitRange(Range<T> range, Node<T> *parentNode){
	vector<Node<T> *> childNodes = parentNode->getChildNodes();
	vector<Range<T> > result;
	int i = 0;
	try{
		for (; i < childNodes.size(); i++){
			Range<T> curRange = childNodes[i]->getRange;
			if (range.atLeft(curRange)){
				result.push(range);
				break;
			}
			else if (range.leftOverlap(curRange)){
				Range<T> tempResult(range.first, curRange.first); // overlap at the margin
				result.push(tempResult);
				break;  
			}
			else if (range.contain(curRange)){
				if (range.first != curRange.first){
					Range<T> tempResult(range.first, curRange.first); // overlap at the margin
					result.push(tempResult);
				}

				if (range.second != curRange.second){
					range.first = curRange.second;
				}
				else{
					break;
				}
			}
			else{ // right overlap or at right
				if (range.first < curRange.second){
					range.first = curRange.second;
				}
			}
		}
	}

	catch (string e){
		cerr<<e<<endl;
	}

	if (i == childNodes.size()){
		result.push_back(range);
	}

	return result;
}

template <class T >
vector<Node<T> *> RoutingTree<T>::insert(vector<Range<T> > subRanges, Node<T> *parentNode){
	
}

template <class T >
int checkRange(Range<T> range, Node<T> *node, Node<T> *subNode) {
	if (node->subRange.size() == 0) {
		return 2;
	}
	for (int i = 0; i != node.subRange.size() && !range.atRight(node.subRange[i]->range); i++) {
		if (range.overlap(node.subRange[i]->Range)) {
			if (range.contain(node.subRange[i]->range) && range.isContainedBy(node.subRange[i]->range)) {
				return 1;
			}
			if (range.contain(node.subRange[i]->range)) {
				subNode = *iter;
				return 0;
			}
			return 3;
		}
	}
	return 2;
}

/* AdaptiveRouting */

#endif
