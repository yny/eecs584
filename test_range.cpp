#include <iostream>
#include "range.h"

using namespace std;

int main(){
	range<int> *p = new range<int>(2,3);
	range<int> *q = new range<int>(1,4);
	//p->first = 0;
	//p->second = 1;
	cout<<p->first<<":"<<p->second<<endl;
	cout<<q->first<<":"<<q->second<<endl;
	cout<<q->contain(p)<<endl;
	cout<<q->overlap(p)<<endl;
	return 0;
}