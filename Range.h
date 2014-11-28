#ifndef RANGE_H
#define RANGE_H

#include <iostream>
#include <cstdlib>

using namespace std;

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
//enum range_cmp {IS_CONTAINED_BY, CONTAINS, LEFT_OVERLAP, RIGHT_OVERLAP, AT_LEFT, AT_RIGHT};

	class Range : public std::pair<T, T>{
	public:
		Range(T low = 0, T high = 0){
			if (low  > high){
				throw "ERROR: Lower bound is larger than upper bound!\n";
			}
			this->first = low; 
			this->second = high;
		}

		void setRange(T low, T high){
			if (low  > high){
				throw "ERROR: Lower bound is larger than upper bound!\n";
			}
			this->first = low; 
			this->second = high;
		}

		bool single(){
			return (this->first == this->second);
		}

		bool isContainedBy(Range *a){
			return (this->first >= a->first) && (this->second <= a->second);
		}

		bool contains(Range *a){
			return (this->first <= a->first) && (this->second >= a->second);
		}

		bool leftOverlap(Range *a){
			return (this->first >= a->first && this->second <= a->second);
		}

		bool rightOverlap(Range *a){
			return (this->second >= a->first && this->second <= a->second);
		}

		bool overlap(Range *a){
			return leftOverlap(a) || rightOverlap(a) || contains(a);
		}

	// No Overlap
		bool atLeft(Range *a){
			return (this->second <= a->first);
		}

		bool atRight(Range *a){
			return (this->first >= a->second);
		}

	// For testing
		void print(){
			cout << "(" << this->first << "," << this->second << ")" << endl;
		}
	};

#endif