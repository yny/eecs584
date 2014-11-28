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
	set<Node<T> *> childNodes = parentNode->getChildNodes();
	set<Node<T> *>::iterator it = childNodes.begin();
	vector<Range<T> > result;
	try{
		for (; it < childNodes.end(); it++){
			Range<T> curRange = (*it)->getRange;
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

	if (it == childNodes.end()){
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
	set<Node<T> *>::iterator iter;
	for (iter = node.subRange.begin(); iter != node.subRange.end() && !range.atRight((*iter)->range); iter++) {
		if (range.overlap((*iter)->Range)) {
			if (range.contain((*iter)->range) && range.isContainedBy((*iter)->range)) {
				return 1;
			}
			if (range.contain((*iter)->range)) {
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
