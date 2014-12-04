#include "RoutingTree.h"

/* Routing Tree */
template <class T >
RoutingTree<T>::RoutingTree(Node<T> *root){
	this->root = new Node<T>(root->getRange());
}

template <class T >
vector<Node<T> *> RoutingTree<T>::getShardIDs(Range<T> range, Node<T> **parentNode) {
	//range not contained in the root
	if (!root->getRange().contains(range)) {
		bool overlap = root->getRange().overlap(range);
		
		//create a new root
		Range<T> newRange = root->getRange().merge(range);
		Node<T> *newRoot = new Node<T>(newRange);
		newRoot->insertChildNode(root);
		root = newRoot;
		*parentNode = root;
		
		if (overlap) {
			return insert(splitRange(range, root), root);
		} else {
			return insert(vector<Range<T> >(1, range), root);
		}
	}
	
	Node<T> *node = root;
	while (1) {
		Node<T> *subNode = NULL;
		switch (checkRange(range, node, &subNode))
		{
		//contained in a subRange
			case 0:
			node = subNode;
			break;
		//exactly the same as a subRange
			case 1:
			*parentNode = node;
			return vector<Node<T> *>(1, node);
		//no overlap with an subRange
			case 2:
			*parentNode = node;
			return insert(vector<Range<T> >(1, range), node);
		//overlap with more than one subRange
			default:
			*parentNode = node;
			vector<Range<T> > ranges = splitRange(range, node);
			if (ranges.size()) {
				return insert(ranges, node);
			} else {
				return vector<Node<T> *>();
			}
		}
	}
} // -> return result node

/*
template <class T >
Node<T> *RoutingTree<T>::search(Range<T> range){
	
} // -> return pointer of Parent Node
*/

template <class T >
vector<Range<T> > RoutingTree<T>::splitRange(Range<T> range, Node<T> *parentNode){
	vector<Node<T> *> childNodes = parentNode->getChildNodes();
	vector<Range<T> > result;
	int i = 0;
	try{
		for (; i < childNodes.size(); i++){
			Range<T> curRange = childNodes[i]->getRange();
			if (range.atLeft(curRange)){
				result.push_back(range);
				break;
			}
			else if (range.leftOverlap(curRange)){
				Range<T> tempResult(range.first, curRange.first); // overlap at the margin
				result.push_back(tempResult);
				break;  
			}
			else if (range.isContainedBy(curRange)){
				break;
			}
			else if (range.contains(curRange)){
				if (range.first != curRange.first){
					Range<T> tempResult(range.first, curRange.first); // overlap at the margin
					result.push_back(tempResult);
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
	Range<T> parentNodeRange = parentNode->getRange();
	vector<Node<T> *> childrenNodes = parentNode->getChildNodes();
	vector<Node<T> *> result;
	int childrenNodesIndex = 0, subRangeIndex = 0;
	cout << "parentNode before insertion: ... \n";
	//DisplayCoveredRanges(parentNode);
	parentNode->printChildNodes();
	try{
		/* Error Handling Section */
		if (subRanges.size() == 0)
		{
			throw "ERROR: no subranges need to be inserted!\n";
		}
		for (int i = 0; i < subRanges.size(); i++)
		{
			Range<T> currentSubRange = subRanges.at(i);
			if (!parentNodeRange.contains(currentSubRange))
			{
				throw "ERROR: One or more splitted subrange exceeded the parent range! \n";
			}
			for (int j = i + 1; j < subRanges.size(); j++)
			{
				Range<T> rangeToBeChecked = subRanges.at(j);
				if (currentSubRange.overlap(rangeToBeChecked))
				{
					throw "ERROR: overlap in subranges! \n";
				}
			}	
		}
		/* Insertion */
		for (; childrenNodesIndex < childrenNodes.size(); childrenNodesIndex++)
		{
			Range<T> currentChildRange = (childrenNodes.at(childrenNodesIndex))->getRange();
			Range<T> currentSubRange = subRanges.at(subRangeIndex);
			if (currentChildRange.atLeft(currentSubRange))
			{
				//result.push_back(childrenNodes.at(childrenNodesIndex));
			}
			else if (currentSubRange.atLeft(currentChildRange))
			{
				Node<T> *newNode = new Node<T>(currentSubRange);
				parentNode->insertChildNode(newNode);
				result.push_back(newNode);
				//result.push_back(childrenNodes.at(childrenNodesIndex));
				if (++subRangeIndex < subRanges.size())
				{
					if ((subRanges.at(subRangeIndex)).equals(currentChildRange))
					{
						subRangeIndex++;
					}
				}
				else
				{
					break;
				}
			}
			else if (currentSubRange.equals(currentChildRange))
			{
				//result.push_back(childrenNodes.at(childrenNodesIndex));
				subRangeIndex++;
			}
			else
			{
				throw "Error:possible overlapping! \n";
			}
		}
		if (subRangeIndex < subRanges.size())
		{
			Node<T> *newNode = new Node<T>(subRanges.at(subRangeIndex));
			parentNode->insertChildNode(newNode);
			result.push_back(newNode);
		}
	}

	catch (string e){
		cerr<<e<<endl;
	}
	cout << "After Insertion: ... \n";
	//DisplayCoveredRanges(parentNode);
	//parentNode -> printChildNodes();
	return result;
}

template <class T >
int RoutingTree<T>::checkRange(Range<T> range, Node<T> *node, Node<T> **subNode) {
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

/* AdaptiveRouting */

