#include "RoutingTree.h"

/* Routing Tree */

RoutingTree::RoutingTree(Node *root){
	this.root = new Node(root->range);
}

vector<Node *> RoutingTree::getShardIDs(Range range, Node *parentNode){
	//range not contained in the root
	if (!range.overlap(root->range)) {
		//create a new root
		Range newRange(range.first, range.second);
		Node *newRoot = new Node(newRange);
		newRoot->subRange.insert(root);
		root = newRoot;
		
		parentNode = root;
		return insert(vector<Range>(1, range), root);
	}
	
	Node *node = root;
	while (1) {
		Node *subNode = NULL;
		switch (checkRange(range, node, subNode))
		{
		//contained in a subRange
		case '0':
			node = subNode;
			break;
		//exactly the same as a subRange
		case '1':
			parentNode = node;
			return vector<Node>(1, node);
		//no overlap with an subRange
		case '2':
			parentNode = node;
			return insert(vector<Range>(1, range), node);
		//overlap with some subRanges
		default:
			parentNode = node;
			return insert(splitRange(range, node), node);
		}
	}
} // -> return result node

Node *RoutingTree::search(Range range){
	
} // -> return pointer of Parent Node

vector<Range> RoutingTree::splitRange(Range range, Node *parentNode){
	
}

vector<Node *> RoutingTree::insert(vector<Range> subRanges, Node *parentNode){
	
}

int checkRange(Range range, Node *node, Node *subNode) {
	if (node->subRange.size() == 0) {
		return 2;
	}
	set<Node *, Cmp>::iterator iter;
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
