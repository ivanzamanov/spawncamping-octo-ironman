#ifndef __WALKERS_H__
#define __WALKERS_H__

#include<iostream>
#include<deque>

#include"DAG.hpp"

void printDFS(const DirectedAcyclicGraph& graph) {
  std::vector<int> stack;
  stack.push_back(0);
  while(!stack.empty()) {
    int vertex = stack.back();
    stack.pop_back();
    std::cout << vertex << '\n';
    const DirectedAcyclicGraph::ChildrenList children = graph.children(vertex);
    DirectedAcyclicGraph::ChildrenList::const_iterator it = children.begin();
    while(it != children.end()) {
      stack.push_back(*it);
    }
  }
}

void printDFSHelper(int vertex, const DirectedAcyclicGraph& graph) {
    std::cout << vertex << '\n';
    const DirectedAcyclicGraph::ChildrenList children = graph.children(vertex);
    DirectedAcyclicGraph::ChildrenList::const_iterator it = children.begin();
    while(it != children.end()) {
      printDFSHelper(*it, graph);
    }
}

void printDFSRec(const DirectedAcyclicGraph& graph) {
  printDFSHelper(0, graph);
}

void printBFS(const DirectedAcyclicGraph& graph) {
  std::deque<int> queue;
  queue.push_back(0);
  while(!queue.empty()) {
    int vertex = stack.front();
    stack.pop_front();
    std::cout << vertex << '\n';
    const DirectedAcyclicGraph::ChildrenList children = graph.children(vertex);
    DirectedAcyclicGraph::ChildrenList::const_iterator it = children.begin();
    while(it != children.end()) {
      stack.push_back(*it);
    }
  }
}

#endif
