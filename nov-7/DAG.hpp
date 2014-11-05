#ifndef __DAG_H__
#define __DAG_H__

#include<cstdlib>
#include<vector>
#include<stack>

#include"../oct-24/stack.hpp"

class DirectedAcyclicGraph {
public:
  DirectedAcyclicGraph();
  DirectedAcyclicGraph(const DirectedAcyclicGraph& other);
  ~DirectedAcyclicGraph();

  // Construct a new vertex in the graph
  int vertex();
  // Delete the given vertex from the graph
  void delete_vertex(int v);
  // Add an edge between the given vertices
  // if one does not already exist
  void edge(int src, int dest);
  // true <=> an edge between the vertices exists
  bool has_edge(int src, int dest);
  // Delete the edge between the given vertices
  // if one exists
  void deleteEdge(int src, int dest);

private:
  typedef std::vector<int> IntStack;
  IntStack deleted;
  typedef std::vector<int> ChildrenList;
  typedef std::vector< ChildrenList > NodesList;

  NodesList nodes;
  int lastNode;
};

#endif
