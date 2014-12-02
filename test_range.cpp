#include <iostream>
#include <vector>
#include "Range.h"

using namespace std;

vector<Range<int> > splitRange(Range<int> range, vector<Range<int> > childRanges);

int main(){
	Range<int> p, q;
	p.setRange(5,10);
	//p->first = 0;
	//p->second = 1;
	//vector<Range<int> > childRanges;
	//vector<Range<int> > result;

	//childRanges.push_back(p);
	//p.setRange(9,10);
	//childRanges.push_back(p);

	//p.setRange(0,7);
	while (1){
		cin >> q.first >> q.second;
		if (q.first > q.second){break;}
		cout << q.overlap(p)<<endl;
	}
	//result = splitRange(p, childRanges);

	/*for (int i = 0; i < result.size(); i ++){
		result[i].print();
	}*/

	return 0;
}

vector<Range<int> > splitRange(Range<int> range, vector<Range<int> > childRanges){
	vector<Range<int> >::iterator it = childRanges.begin();
	vector<Range<int> > result;
    try{
	for (; it < childRanges.end(); it++){
		Range<int> curRange = (*it);
		if (range.atLeft(curRange)){
			result.push_back(range);
			break;
		}
		else if (range.leftOverlap(curRange)){
			Range<int> tempResult(range.first, curRange.first); // overlap at the margin
			result.push_back(tempResult);
			break;  
		}
		else if (range.contains(curRange)){
			if (range.first != curRange.first){
				Range<int> tempResult(range.first, curRange.first); // overlap at the margin
				result.push_back(tempResult);
			}
			if (range.second != curRange.second){
				range.first = curRange.second;
			}
			else {
				break;
			}
		}
		else{ // right overlap or at right
			if (range.first < curRange.second){
				range.first = curRange.second;
			}
		}
	}

	if (it == childRanges.end()){
		result.push_back(range);
	}

    }
	catch (string e){
		cerr<<e<<endl;
	}
	return result;
}