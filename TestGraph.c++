// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Graph.c++ TestGraph.c++ -o TestGraph -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestGraph

To obtain coverage of the test:
    % gcov-4.7 -b Graph.c++ TestGraph.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;};

#define ALL_OF_IT       typedef typename TestFixture::graph_type         graph_type; \
                        typedef typename TestFixture::vertex_descriptor  vertex_descriptor; \
                        typedef typename TestFixture::edge_descriptor    edge_descriptor; \
                        typedef typename TestFixture::vertex_iterator    vertex_iterator; \
                        typedef typename TestFixture::edge_iterator      edge_iterator; \
                        typedef typename TestFixture::adjacency_iterator adjacency_iterator; \
                        typedef typename TestFixture::vertices_size_type vertices_size_type; \
                        typedef typename TestFixture::edges_size_type    edges_size_type;

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef testing::Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        my_types;

TYPED_TEST_CASE(TestGraph, my_types);

TYPED_TEST(TestGraph, add_edge_1) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(true, p1.second);
    
    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);
}
TYPED_TEST(TestGraph, add_edge_2) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    std::pair<edge_descriptor, bool> p2 = add_edge(vdB, vdA, g);
    ASSERT_EQ(true, p1.second);
    ASSERT_EQ(true, p2.second);
    
    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);
}
TYPED_TEST(TestGraph, add_edge_3) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    std::pair<edge_descriptor, bool> p2 = add_edge(vdC, vdB, g);
    ASSERT_EQ(true, p1.second);
    ASSERT_EQ(true, p2.second);
    
    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);
}
TYPED_TEST(TestGraph, add_vertex_1) {
    ALL_OF_IT
    
    graph_type g;
    ASSERT_EQ(0, num_vertices(g));
    vertex_descriptor vdA = add_vertex(g);
    ASSERT_EQ(1, num_vertices(g));
    vertex_descriptor vdB = add_vertex(g);
    
    add_edge(vdA, vdB, g);
    //ASSERT_EQ(true, p1.second);
    
    edges_size_type es = num_vertices(g);
    ASSERT_EQ(2, es);
}
TYPED_TEST(TestGraph, add_vertex_2) {
    ALL_OF_IT
    
    graph_type g;
    ASSERT_EQ(0, num_vertices(g));
    vertex_descriptor vdA = add_vertex(g);
    ASSERT_EQ(1, num_vertices(g));
    vertex_descriptor vdB = add_vertex(g);
    
    add_edge(vdA, vdB, g);
    //ASSERT_EQ(true, p1.second);
    
    edges_size_type es = num_vertices(g);
    ASSERT_EQ(2, es);
    
    add_vertex(g);
    add_vertex(g);
    
    ASSERT_EQ(4, num_vertices(g));
}
TYPED_TEST(TestGraph, add_vertex_3) {
    ALL_OF_IT
    
    graph_type g;
    ASSERT_EQ(0, num_vertices(g));
    vertex_descriptor vdA = add_vertex(g);
    ASSERT_EQ(1, num_vertices(g));
    vertex_descriptor vdB = add_vertex(g);
    
    add_edge(vdA, vdB, g);
    //ASSERT_EQ(true, p1.second);
    
    edges_size_type es = num_vertices(g);
    ASSERT_EQ(2, es);
    
    add_vertex(g);
    add_vertex(g);
    
    ASSERT_EQ(4, num_vertices(g));
    
    add_vertex(g);
    add_vertex(g);
    
    ASSERT_EQ(6, num_vertices(g));
}

TYPED_TEST(TestGraph, adj_vert_1) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdB, vdA, g);
    std::pair<edge_descriptor, bool> p2 = add_edge(vdB, vdC, g);
    ASSERT_EQ(true, p1.second);
    ASSERT_EQ(true, p2.second);
    
    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);
    
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdB, g);
    adjacency_iterator                             b = p.first;
    adjacency_iterator                             e = p.second;
    
    //vertex_iterator vi = adjacent_vertices(vdB, g).first;
    ASSERT_EQ(vdA, *b);
    ++b;
    ASSERT_EQ(vdC, *b);
}
TYPED_TEST(TestGraph, adj_vert_2) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdB, vdA, g);
    std::pair<edge_descriptor, bool> p2 = add_edge(vdC, vdB, g);
    ASSERT_EQ(true, p1.second);
    ASSERT_EQ(true, p2.second);
    
    edges_size_type es = num_edges(g);
    ASSERT_EQ(2, es);
    
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdB, g);
    adjacency_iterator                             b = p.first;
    adjacency_iterator                             e = p.second;
    
    //vertex_iterator vi = adjacent_vertices(vdB, g).first;
    ASSERT_EQ(vdA, *b);
    ++b;
    //ASSERT_EQ(vdC, *b);
}
TYPED_TEST(TestGraph, adj_vert_3) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdB, vdB, g);
    ASSERT_EQ(true, p1.second);
    
    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);
    
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdB, g);
    adjacency_iterator                             b = p.first;
    adjacency_iterator                             e = p.second;
    
    ASSERT_EQ(vdB, *b);
}
TYPED_TEST(TestGraph, adj_vert_4) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    
    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);
}


TYPED_TEST(TestGraph, edge_1) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);
    
    std::pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);
    
    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);
    
    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);
    
    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}
TYPED_TEST(TestGraph, edge_2) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);
    
    std::pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);
    
    std::pair<edge_descriptor, bool> p3 = edge(vdA, vdC, g);
    //ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(false, p3.second);
}
TYPED_TEST(TestGraph, edge_3) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    
    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);
    
    std::pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);
    
    std::pair<edge_descriptor, bool> p3 = edge(vdA, vdC, g);
    ASSERT_EQ(edAC, p3.first);
    ASSERT_EQ(true, p3.second);
}



TYPED_TEST(TestGraph, edges_1) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    
    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);
}
TYPED_TEST(TestGraph, edges_2) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    
    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edBC, ed);}
    ++b;
    ASSERT_EQ(e, b);
}
TYPED_TEST(TestGraph, edges_3) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;

    ASSERT_EQ(e, b);
}



TYPED_TEST(TestGraph, num_edges_1) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    
    
    ASSERT_EQ(3, num_edges(g));
}
TYPED_TEST(TestGraph, num_edges_2) {
    ALL_OF_IT
    
    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
     ASSERT_EQ(1, num_edges(g));
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    ASSERT_EQ(2, num_edges(g));
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    
    
    ASSERT_EQ(3, num_edges(g));
}
TYPED_TEST(TestGraph, num_edges_3) {
    ALL_OF_IT
    
    graph_type g;
    ASSERT_EQ(0, num_edges(g));
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    
    
    ASSERT_EQ(3, num_edges(g));
    
    add_edge(vdB, vdC, g);
    
    ASSERT_EQ(3, num_edges(g));
}


TYPED_TEST(TestGraph, num_vert_1) {
    ALL_OF_IT
    
    graph_type g;
    ASSERT_EQ(0, num_edges(g));
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    
    
    ASSERT_EQ(3, num_vertices(g));

}
TYPED_TEST(TestGraph, num_vert_2) {
    ALL_OF_IT
    
    graph_type g;
    ASSERT_EQ(0, num_vertices(g));
    vertex_descriptor vdA = add_vertex(g);
    ASSERT_EQ(1, num_vertices(g));
    vertex_descriptor vdB = add_vertex(g);
    ASSERT_EQ(2, num_vertices(g));
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    
    
    ASSERT_EQ(3, num_vertices(g));
    
}
TYPED_TEST(TestGraph, num_vert_3) {
    ALL_OF_IT
    
    graph_type g;
    for(int i = 0; i < 100; i++)
        add_vertex(g);
    
    
    ASSERT_EQ(100, num_vertices(g));
}















TYPED_TEST(TestGraph, source_1) {
    ALL_OF_IT
    using namespace std;
    
    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    //cout << "vdA"  << endl;
    vertex_descriptor vdB = add_vertex(g);
    //vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    
    ASSERT_EQ(source(edAB, g), 0);
    ASSERT_EQ(0, vdA);
}







TYPED_TEST(TestGraph, source_2) {
    ALL_OF_IT
    
    using namespace std;
    
    
    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    //cout << "vdA" << vdA << endl;
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    //cout << "edAB" << edAB << endl;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    
    ASSERT_EQ(source(edAB, g), vdA);
    ASSERT_EQ(source(edAC, g), vdA);
    ASSERT_EQ(source(edBC, g), vdB);
    
    //exit(0);

}

TYPED_TEST(TestGraph, source_3) {
    ALL_OF_IT
    
    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    
    ASSERT_EQ(source(edAA, g), vdA);
}




TYPED_TEST(TestGraph, target_1) {
    ALL_OF_IT
    
    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    //vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    
    ASSERT_EQ(target(edAB, g), vdB);
}
TYPED_TEST(TestGraph, target_2) {
    ALL_OF_IT
    
    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    
    ASSERT_EQ(target(edAB, g), vdB);
    ASSERT_EQ(target(edAC, g), vdC);
    ASSERT_EQ(target(edBC, g), vdC);
    
}

TYPED_TEST(TestGraph, target_3) {
    ALL_OF_IT
    
    graph_type g;
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    edge_descriptor edAA = add_edge(vdA, vdA, g).first;
    
    ASSERT_EQ(target(edAA, g), vdA);
}



TYPED_TEST(TestGraph, vertex_1) {
    ALL_OF_IT

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);
}
TYPED_TEST(TestGraph, vertex_2) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    
    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);
    
    vertex_descriptor vd2 = vertex(1, g);
    ASSERT_EQ(vdB, vd2);
    
    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(2, vs);
}
TYPED_TEST(TestGraph, vertex_3) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);
    
    vertex_descriptor vd2 = vertex(1, g);
    ASSERT_EQ(vdB, vd2);
    
    vertex_descriptor vd3 = vertex(2, g);
    ASSERT_EQ(vdC, vd3);
    
    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(3, vs);
}



TYPED_TEST(TestGraph, vertices_1) {
    ALL_OF_IT
    
    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);
}
TYPED_TEST(TestGraph, vertices_2) {
    ALL_OF_IT
    
    graph_type g;
    
    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    
    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);
}
TYPED_TEST(TestGraph, vertices_3) {
    ALL_OF_IT
    
    graph_type g;
    
    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    
    ASSERT_EQ(e, b);
}

