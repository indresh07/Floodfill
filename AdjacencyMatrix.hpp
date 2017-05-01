#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX 1
#include "GraphAdjacencyBase.hpp"
using namespace std;
using namespace cs202;

class AdjacencyMatrix : public GraphAdjacencyBase {

private:

	int** adjMatrix;
	int nVertices;

public:
	AdjacencyMatrix(int v);
	~AdjacencyMatrix();

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

	void display(){
		for(int i = 0; i < nVertices; i++){
			for(int j = 0; j < nVertices; j++)
				cout<<adjMatrix[i][j]<<" ";

			cout<<"\n";
		}
	}

	LinearList<LinearList<int> > getAdjacent();
};

AdjacencyMatrix::AdjacencyMatrix(int v){

	nVertices = v;
	adjMatrix = new int*[nVertices];

	for(int i = 0; i < nVertices; i++){
		adjMatrix[i] = new int[nVertices];

		for (int j = 0; j < nVertices; j++){
			adjMatrix[i][j] = 0;
		}
	}
}

AdjacencyMatrix::~AdjacencyMatrix(){

	for (int i = 0; i < nVertices; ++i){
		
		delete[] adjMatrix[i];
	}

	delete[] adjMatrix;
}

bool AdjacencyMatrix::edgeExists(int i, int j){


	if(adjMatrix[i][j] == 1)
		return true;
	else
		return false;
}

int AdjacencyMatrix::vertices(){

	return nVertices;
}

int AdjacencyMatrix::edges(){

	int nEdges = 0;

	for(int i = 0; i < nVertices; i++)
		for (int j = 0; j < nVertices; j++)
			if(adjMatrix[i][j] == 1)
				nEdges++;

	return nEdges;
}

void AdjacencyMatrix::add(int i, int j){

	if(adjMatrix[i][j] == 0)
		adjMatrix[i][j] = 1;
	else
		throw "Edge already exists.";
}

void AdjacencyMatrix::remove(int i, int j){

	if(adjMatrix[i][j] == 1)
		adjMatrix[i][j] = 0;
	else
		throw "Edge does not  exists.";
}

int AdjacencyMatrix::degree(int i){

	int nDegree = 0;

	for(int j = 0; j < nVertices; j++)
		if(adjMatrix[i][j] == 1)
			nDegree++;

	for(int j = 0; j < nVertices; j++)
		if(adjMatrix[j][i] == 1)
			nDegree++;

	return nDegree;
}

LinearList<LinearList<int> > AdjacencyMatrix::getAdjacent(){
	LinearList<LinearList<int> > adjNodes(nVertices);

	for(int i = 0; i < nVertices; i++)
		for(int j = 0; j < nVertices; j++)
			if(adjMatrix[i][j] == 1)
				adjNodes[i].push_back(j);

	return adjNodes; 
}


#endif /* ifndef ADJACENCY_MATRIX */