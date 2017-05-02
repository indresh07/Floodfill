#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST 1
#include "GraphAdjacencyBase.hpp"

using namespace cs202;
using namespace std;

class AdjacencyList : public GraphAdjacencyBase {

private:
	LinearList<list<int> > adjList;
	int nVertices;

public:

	AdjacencyList(int v);
	~AdjacencyList(){};

	/*
	 * Function: edgeExists
	 * Returns true if an edge exists between vertices i and j, false otherwise.
	 */
	bool edgeExists(int i, int j);
	/*`
	 * Function: vertices
	 * Returns the number of vertices in the adjacency structure.
	 */
	int vertices();
	/*
	 * Function: edges
	 * Returns the number of edges in the adjacency structure.
	 */
	int edges();
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
	 * Function: degree
	 * Returns the degree of the vertex i
	 */
	int degree(int i);
	/*
     * Function: getAdjacent
     * Returns array of adjacent nodes of vertex i
     */ 
	LinearList<LinearList<int> > getAdjacent();

	void display(){
		for(int i = 0; i < nVertices; i++){
			node<int>* iterator = adjList[i].getIterator();

			while(iterator){
				cout<<iterator->data<<" ";
				iterator = iterator->next;
			}			
			cout<<"\n";
		}
	}
};

AdjacencyList::AdjacencyList(int v){

	nVertices = v;
	adjList.resize(v);
}

bool AdjacencyList::edgeExists(int i, int j){

	node<int>* iterator = adjList[i].getIterator();

	while(iterator){
		if(iterator->data == j)
			return true;
		iterator = iterator->next;
	}

	return false;
}
	
int AdjacencyList::vertices(){
	return nVertices;
}
	
int AdjacencyList::edges(){
	int nEdges = 0;

	for(int i = 0; i < nVertices; i++)
		nEdges += adjList[i].length();

	return nEdges;
}
	
void AdjacencyList::add(int i, int j){

	if(!edgeExists(i, j))
		adjList[i].append(j);
	else
		throw "Edge already exists";
}

void AdjacencyList::remove(int i, int j){

	if(!edgeExists(i, j))
		adjList[i].remove(j);
	else
		throw "Edge does not exists";
}

int AdjacencyList::degree(int i){

	int nDegree = adjList[i].length();

	for(int j = 0; j < nVertices; j++)
		if(j != i && edgeExists(j, i))
			nDegree++;

	return nDegree;
}

LinearList<LinearList<int> > AdjacencyList::getAdjacent(){

	LinearList<LinearList<int> > adjNodes(nVertices);

	for(int i = 0; i < nVertices; i++){
		node<int>* iterator = adjList[i].getIterator();

		while(iterator){

			adjNodes[i].push_back(iterator->data);
			iterator = iterator->next;
		}
	}

	return adjNodes;


}
#endif /* ifndef ADJACENCY_LIST */