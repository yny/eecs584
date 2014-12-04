#include <iostream>
#include <vector>
#include "Range.h"
#include "Node.h"
#include "Node.cpp"

using namespace std;
template<class T>
vector<Node<T> *> TreeInsert(vector<Range<T> > subRanges, Node<T> *parentNode);

template<class T>
void DisplayCoveredRanges(Node<T> * node){
	cout << "Current Ranges in the Node...\n" ;
	cout << (node->getRange()).first << "\t" << (node->getRange()).second << "\n";
}

int main(){
	Range<int> r0 = Range<int>(1, 10);
	Range<int> r1 = Range<int>(1, 2);
	Range<int> r2 = Range<int>(4, 5);
	Range<int> r3 = Range<int>(6, 7);
	vector<Range<int> > subRanges;
	subRanges.push_back(r1);
	subRanges.push_back(r2);
	subRanges.push_back(r3);
	Node<int> *root = new Node<int>(r0);
	Node<int> *nodeA = new Node<int>(r2);
	root -> insertChildNode(nodeA);
	root -> printChildNodes();
	vector<Node<int> *> myResult = TreeInsert(subRanges, root);
}

template<class T>
vector<Node<T> *> TreeInsert(vector<Range<T> > subRanges, Node<T> *parentNode){
	Range<T> parentNodeRange = parentNode->getRange();
	vector<Node<T> *> childrenNodes = parentNode->getChildNodes();
	vector<Node<T> *> result;
	int childrenNodesIndex = 0, subRangeIndex = 0;
	cout << "parentNode before insertion: ... \n";
	DisplayCoveredRanges(parentNode);
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
				result.push_back(childrenNodes.at(childrenNodesIndex));
			}
			else if (currentSubRange.atLeft(currentChildRange))
			{
				Node<T> *newNode = new Node<T>(currentSubRange);
				parentNode->insertChildNode(newNode);
				result.push_back(newNode);
				result.push_back(childrenNodes.at(childrenNodesIndex));
				subRangeIndex += 2;
			}
			else if (currentSubRange.equals(currentChildRange))
			{
				result.push_back(childrenNodes.at(childrenNodesIndex));
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
	DisplayCoveredRanges(parentNode);
	parentNode -> printChildNodes();
	return result;
}