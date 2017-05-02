#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH 1
#include "AbstractGraph.hpp"

using namespace std;
using namespace cs202;
/*
 * A class to represent a directed graph.
 */
class DirectedGraph : public AbstractGraph {
private:

  GraphAdjacencyBase* graph;

  int getIndex(int i){
    for(int j = 0; j < graph->vertices(); j++)
    if(AbstractGraph::verticesMap[j] == i){
      return j;
    }  

    return -1;
  }
public:
  /*
   * Constructor: DirectedGraph
   *
   * Parameters: mode
   * Used to decide which representation to use
   * 'm' for AdjacencyMatrix
   * 'l' for AdjacencyList
   */
  DirectedGraph(int numVertices, char rep);
  /*
   * Function: indegree
   * Returns the indegree of a vertex
   */
  int indegree(int i);
  /*
   * Function: outdegree
   * Returns the outdegree of a vertex.
   */
  int outdegree(int i);
  /*
   * Function: edgeExists
   * Returns true if an edge exists between vertices i and j, false otherwise.
   */
  bool edgeExists(int i, int j);
  /*
   * Function: edges
   * Returns the number of edges in the adjacency structure.
   */
  int edges();
  /*
   * Function: vertices
   * Returns the number of vertices in the adjacency structure.
   */
  int vertices();
  /*
   * Function add:
   * Adds an edge between vertices i and j
   */
  void add(int i, int j);
  /*
   * Function: remove
   * Deleted the edge between vertices i and j
   */
  void remove(int i, int j);
  /*
   * Function dfs:
   * Does a depth first traversal of the entire graph.
   * Runs the given function work, with the value of each vertex.
   */
  void dfs(void (*work)(int&));
  /*
   * Function bfs:
   * Does a breadth first traversal of the entire graph.
   * Runs the given function work, with the value of each vertex.
   */
  void bfs(void (*work)(int&));
};

DirectedGraph::DirectedGraph(int numVertices, char rep){

  AbstractGraph::verticesMap.resize(numVertices);

  if(rep != 'm' && rep != 'M' && rep != 'l' && rep != 'L'){
    cout<<"**Invalid mode. Using adjacency list mode as default.\n";
    rep = 'l';
  }

  if(rep == 'm' || rep == 'M'){
    graph = new AdjacencyMatrix(numVertices);
  }
  else{
    graph = new AdjacencyList(numVertices); 
  }

  cout<<"Enter vertices : \n";
  int vertex;
  for(int i = 0; i < numVertices; i++){
    cout<<"["<<i+1<<"] : ";
    cin>>vertex;
    AbstractGraph::verticesMap.push_back(vertex);
  }
}

int DirectedGraph::indegree(int i){

  int src = getIndex(i);
  if(src == -1)
    throw "Vertex not found.";

  int degree = 0;
  for(int j = 0; j < graph->vertices(); j++){
    if(j != src && graph->edgeExists(j, src))
      degree++;
  }

  return degree;
}

int DirectedGraph::outdegree(int i){

  int src = getIndex(i);
  if(src == -1)
    throw "Vertex not found.";

  int degree = 0;
  for(int j = 0; j < graph->vertices(); j++){
    if(j != src && graph->edgeExists(src, j))
      degree++;
  }

  return degree;
}

bool DirectedGraph::edgeExists(int i, int j){
  int src = getIndex(i);
  int dest = getIndex(j);

  if(src == -1 || dest == -1)
    throw "Source/Destination not found.";

  return graph->edgeExists(src, dest);
}

int DirectedGraph::edges(){

  return graph->edges();
}

int DirectedGraph::vertices(){

  return graph->vertices();
}

void DirectedGraph::add(int i, int j){

  int src = getIndex(i);
  int dest = getIndex(j);

  if(src == -1 || dest == -1)
    throw "Source/Destination not found.";

  graph->add(src, dest);
}

void DirectedGraph::remove(int i, int j){

  int src = getIndex(i);
  int dest = getIndex(j);

  if(src == -1 || dest == -1)
    throw "Source/Destination not found.";

  graph->remove(src, dest);
}

void DirectedGraph::dfs(void (*work)(int&)){

  Color color[graph->vertices()];

  for(int i = 0; i < graph->vertices(); i++)
    color[i] = WHITE;

  stack<int> dfsStack;

  int i = 0, j;
  LinearList<LinearList<int> > adjNodes = graph->getAdjacent();

  bool allVisited = false;
  while(!allVisited){
    while(!dfsStack.empty()){
       i = dfsStack.top();

      if(adjNodes[i].size() > 0){
        j = adjNodes[i][0];
        adjNodes[i].erase_pos(0);
        if(color[j] == WHITE){
          dfsStack.push(j);
          color[j] = GRAY;
          (*work)(AbstractGraph::verticesMap[j]);
        }
      }
      else{
        color[i] = BLACK;
        dfsStack.pop();
      }
    }

    allVisited = true;
    for(j = 0; j < graph->vertices(); j++)
      if(color[j] == WHITE){
        allVisited = false;
        dfsStack.push(j);
        (*work)(AbstractGraph::verticesMap[j]);
        color[j] = GRAY;
        break;
      }
  }
}

void DirectedGraph::bfs(void (*work)(int&)){
  
  Color color[graph->vertices()];

  for(int i = 0; i < graph->vertices(); i++)
    color[i] = WHITE;

  queue<int> bfsQueue;

  int i = 0, j;
  LinearList<LinearList<int> > adjNodes = graph->getAdjacent();

  bool allVisited = false;
  while(!allVisited){
    while(!bfsQueue.empty()){
       i = bfsQueue.front();

      if(adjNodes[i].size() > 0){
        j = adjNodes[i][0];
        adjNodes[i].erase_pos(0);
        if(color[j] == WHITE){
          bfsQueue.push(j);
          color[j] = GRAY;
          (*work)(AbstractGraph::verticesMap[j]);
        }
      }
      else{
        color[i] = BLACK;
        bfsQueue.pop();
      }
    }

    allVisited = true;
    for(j = 0; j < graph->vertices(); j++)
      if(color[j] == WHITE){
        allVisited = false;
        bfsQueue.push(j);
        (*work)(AbstractGraph::verticesMap[j]);
        color[j] = GRAY;
        break;
      }
  }
}
#endif /* ifndef DIRECTED_GRAPH */