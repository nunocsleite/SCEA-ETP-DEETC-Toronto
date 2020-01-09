#ifndef COMMON_H
#define COMMON_H


#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/reverse_graph.hpp> // For reverse graph


// Use a vector for vertices and a linked list for edges
//typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS> AdjacencyList;

// Use a vector for vertices, a set for edges, and bidirectional graph in order to access the ascending nodes
typedef boost::adjacency_list<boost::setS, boost::vecS, boost::bidirectionalS> AdjacencyList;

typedef boost::reverse_graph<AdjacencyList> Rgraph;
typedef AdjacencyList::vertex_descriptor Vertex;


#endif // COMMON_H
