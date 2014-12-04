#include <iostream>
#include <vector>
#include <String>
#include "Range.h"
#include "Node.h"
#include "Node.cpp"
#include "RoutingTree.h"
#include "RoutingTree.cpp"

using namespace std;

Range<int> getInputRange(string input);
vector<int> getInputIDs(string input);
void updateIds(vector<Node<int> *> newNodes, vector<int> ids);

int main(){
	// Initialize Routing Tree
	Range<int> r0 = Range<int>(10, 20);
	Node<int> *root = new Node<int>(r0);
	RoutingTree<int> *tree = new RoutingTree<int>(root);

	// Get input: (0,1) 1,2,3,4,5 
	string input;
	cin >> input;
	while (input != "END"){
		cout << "======================" <<endl;
		Range<int> r = getInputRange(input);
		cout << ">>>>> Range: ";
		r.print();
		Node<int> * parentNode = new Node<int>(r);
		vector<Node<int> *> newNodes = tree->getShardIDs(r, &parentNode);
		cin >> input;
		vector<int> ids = getInputIDs(input);
		updateIds(newNodes, ids);
		parentNode->printChildNodes();
		cout << "======================" <<endl;

		cin >> input;
	}
	return 0;
}

Range<int> getInputRange(string input){
	Range<int> result(0,0);
	size_t found = input.find(',');
		if (found == string::npos){
			cerr<<"ERROR"<<endl;
		}
		int lower = atoi((input.substr(1, found - 1)).c_str());
		//cout << lower;
		int upper = atoi((input.substr(found + 1, input.length() - found - 2)).c_str());
		//cout << "~" << upper <<endl;


		result = Range<int>(lower, upper);
	return result;
}

vector<int> getInputIDs(string input){
	vector<int> shardIDs;
	cout << ">>>>> IDs: [";
	size_t found = input.find(',');
		while (found != string::npos){
			int id = atoi((input.substr(0, found)).c_str());
			shardIDs.push_back(id);
			cout << id << ",";
			input.erase(0, found + 1);
			found = input.find(',');
		}

		if (!input.empty()){
			int id = atoi(input.c_str());
			cout << id << "]" << endl;
			shardIDs.push_back(id);
		}

	return shardIDs;
}

void updateIds(vector<Node<int> *> newNodes, vector<int> ids){
	for(int i = 0; i < newNodes.size(); i++){
		newNodes[i]->setShards(ids);
	}
}
