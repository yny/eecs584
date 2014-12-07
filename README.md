eecs584 Adaptive Routing Tree
=============================

Files:
	Range.h
	Node.h
	Node.cpp
	RoutingTree.h
	RoutingTree.cpp

To compile:
	make

To run test case:
	make run < test1.in

* The test case should be written in the format similar to test1.in:
	(lower1, upper1) shardID1,shartdID2,....
	(lower2, upper2) shardID3,shartdID4,....
	...
	END

* The output of the testcase will only print out the level of the current node
* and will be similar to following:
	======================
	>>>>> Range: (5,10)
	parentNode before insertion: ...
	size: 1
	(10,20)
	-->
	After Insertion: ...
	>>>>> IDs: [1,2,3,4,5]
	size: 2
	(5,10)
	--> 1 2 3 4 5
	(10,20)
	-->
	======================
	