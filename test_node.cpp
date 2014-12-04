#include <iostream>
#include <vector>
#include "Node.h"
#include "Node.cpp"

using namespace std;

int main(){
	Range<int> range(4,5);
	Node<int> root(range);

	while (1){
		cin >> range.first >> range.second;
		if (range.first > range.second){break;}
		Node<int> * child = new Node<int>(range);
		root.insertChildNode(child);
		root.printChildNodes();
	}
	return 0;
}