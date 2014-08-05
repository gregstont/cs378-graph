all:

clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  TestGraph

config:
	doxygen -g

TestGraph: Graph.h TestGraph.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestGraph.c++ -o TestGraph -lgtest -lgtest_main -lpthread

Test: Graph.h Test.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Test.c++ -o Test -lgtest -lgtest_main -lpthread