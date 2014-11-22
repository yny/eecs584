#include <iostream>
#include <cstdlib>
template <class T >
/*
Structur of the node in the tree must includes:
	range [lower, upper] -> need another struct?
	vector(Array) of shardIDs

Functions includes:
	init()
	insert()
	search()
	merge()?
*/

class range : public std::pair<T, T>{
public:
	range(T low = 0, T high = 0){
		this->first = low; 
		this->second = high;
	}

	bool contain(range *a){
		return (this->first <= a->first) && (this->second >= a->second);
	}

	bool leftOverlap(range *a){
		return (this->first >= a->first && this->first <= a->second);
	}

	bool rightOverlap(range *a){
		return (this->second >= a->first && this->second <= a->second);
	}

	bool overlap(range *a){
		return leftOverlap(a) || rightOverlap(a) || contain(a);
	}
};

