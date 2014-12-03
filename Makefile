out: Range.h RoutingTree.o Node.o
	g++ -o out.o test_insert.cpp 

test_range: Range.h
	g++ -o out.o test_insert.cpp 

test_node: Node.o
	g++ -Wall test_node.cpp -o out

RoutingTree.o: RoutingTree.h
	g++ -Wall -c RoutingTree.cpp

Node.o: Node.h Node.cpp Range.h
	g++ -Wall -c Node.cpp

run:
	./out.o

clean:
	rm *.o
	
