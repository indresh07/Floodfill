/*  Author : Indresh Kumar Gupta
    Purpose : Implementation of undirected graph using both adjacency
              list and adjacency matrix representation
    Version : 1.2

*/

#ifndef UNDIRECTED_GRAPH
#define UNDIRECTED_GRAPH 1
/*
 * A class to represent an UndirectedGraph
 * Subclasses AbstractGraph
 */
#include "AbstractGraph.hpp"
class UndirectedGraph : public AbstractGraph {
 private:

  GraphAdjacencyBase* graph;

 public:
  /*
   * Constructor: UndirectedGraph
   *
   * Parameters: mode
   * Used to decide which representation to use
   * 'm' for AdjacencyMatrix
   * 'l' for AdjacencyList
   */
  UndirectedGraph(int vertices, char mode);
  /*
   * Returns the degree of the vertex.
   */
  int degree(int i);
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

UndirectedGraph::UndirectedGraph(int numVertices, char rep){

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
}

int UndirectedGraph::degree(int i){

  if(edgeExists(i, i))
    return (graph->degree(i) + 3) / 2;
  else
    return graph->degree(i) / 2;
}

bool UndirectedGraph::edgeExists(int i, int j){

  return graph->edgeExists(i, j);
}

int UndirectedGraph::edges(){

  int nEdges = 0;

  for(int i = 0; i < graph->vertices(); i++)
    for(int j = i; j < graph->vertices(); j++)
      if(edgeExists(i, j))
        nEdges++;

  return nEdges;
}

int UndirectedGraph::vertices(){

  return graph->vertices();
}

void UndirectedGraph::add(int i, int j){

  graph->add(i, j);

  if(i != j)
    graph->add(j, i);
}

void UndirectedGraph::remove(int i, int j){

  graph->remove(i, j);
  graph->remove(j, i);
}

void UndirectedGraph::dfs(void (*work)(int&)){

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
          (*work)(j);
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
        (*work)(j);
        color[j] = GRAY;
        break;
      }
  }
}

void UndirectedGraph::bfs(void (*work)(int&)){
  
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
          (*work)(j);
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
        (*work)(j);
        color[j] = GRAY;
        break;
      }
  }
}
#endif /* ifndef UNDIRECTED_GRAPH */