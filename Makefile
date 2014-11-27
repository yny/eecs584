out: range.h rt node
	g++ -o out.o test_range.cpp 

rt: RoutingTree.h
	g++ -o rt RoutingTree.cpp

node: node.h
	g++ -o node node.cpp

run:
	./out.o

clean:
	rm *.o
	