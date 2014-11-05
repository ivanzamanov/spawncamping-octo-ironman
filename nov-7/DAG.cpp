#include"DAG.hpp"

DirectedAcyclicGraph::DirectedAcyclicGraph():lastNode(0) {
  // Nothing
}

DirectedAcyclicGraph::DirectedAcyclicGraph(const DirectedAcyclicGraph& other) {
  nodes = other.nodes;
  deleted = other.deleted;
}

int DirectedAcyclicGraph::vertex() {
  if(!deleted.empty()) {
    int result = deleted.back();
    deleted.pop_back();
    return result;
  } else {
    return ++lastNode;
  }
}

void DirectedAcyclicGraph::delete_vertex(int v) {
  if(v > lastNode)
    return;

  nodes[v].clear();
  NodesList::iterator it = nodes.begin();
  while(it != nodes.end()) {
    ChildrenList::iterator childrenIt = (*it).begin();
    while(childrenIt != (*it).end()) {
      if(*childrenIt == v)
        childrenIt = (*it).erase(childrenIt);
      else
        ++childrenIt;
    }
    ++it;
  }
}

const DirectedAcyclicGraph::ChildrenList& DirectedAcyclicGraph::children(int v) {
  if(v > lastNode) 
    return DirectedAcyclicGraph::ChildrenList();
  return nodes[v];
}

void DirectedAcyclicGraph::edge(int src, int dest) {
  if(!has_edge(src, dest)) {
    nodes[src].push_back(dest);
  }
}

bool DirectedAcyclicGraph::has_edge(int src, int dest) {
  if(src > lastNode || dest > lastNode)
    return false;
  ChildrenList& children = nodes[src];
  ChildrenList::iterator it = children.begin();
  while(it != children.end()) {
    if(*it == dest)
      return true;
    else
      ++it;
  }
  return false;
}

void DirectedAcyclicGraph::deleteEdge(int src, int dest) {
  if(src > lastNode || dest > lastNode)
    return;

  ChildrenList& children = nodes[src];
  ChildrenList::iterator it = children.begin();
  while(it != children.end()) {
    if(*it == dest) {
      children.erase(it);
    } else
      ++it;
  }
}
