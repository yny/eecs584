eecs584 Adaptive Routing Tree
=============================
Section 1:
=============================

To compile:
	make

To run test case:
	make run < test1.in

# The test case should be written in the format similar to test1.in:
	(lower1, upper1) shardID1,shartdID2,....
	(lower2, upper2) shardID3,shartdID4,....
	...
	END

# The output of the testcase will only print out the level of the current node
# and will be similar to following:
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

=============================
Section 2:
=============================

Files:
	Range.h 
	Node.h
	Node.cpp
	RoutingTree.h
	RoutingTree.cpp
	test_RoutingTree.cpp

Major Function:
	The major function of our source codes is implementing the class of Adaptive Routing Tree. 

Rnage.h: 	
	Defines the class of Range and all the comparison relationships

Node.h/cpp:	
	Defines the class of Node and all the operations including: 
	getRange, getShards, setShards, getChildNodes and insertChildNode

RoutingTree.h/cpp
	Defines the class of RoutingTree and all the public operations including: 
	getRoot, setRoot and getSharIDs(Search operation)

	Also all the private operations including:
	search, splitRange, insert and checkRange

test_RoutingTree.cpp
	Provides an interface to test our Adaptive Routing Tree.
		