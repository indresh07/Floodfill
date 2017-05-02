#include <iostream>
#include <stdlib.h>
#include "UndirectedGraph.hpp"

using namespace std;

int options(){

	cout<<"\n[1] Add an edge\n";
	cout<<"[2] Remove an edge\n";
	cout<<"[3] Check an edge\n";
	cout<<"[4] Degree of a vertex\n";
	cout<<"[5] No. of vertices\n";
	cout<<"[6] No. of edges\n";
	cout<<"[7] DFS\n";
	cout<<"[8] BFS\n";
	cout<<"[0] Exit\n";

	int choice;
	cout<<"Enter choice : ";
	cin>>choice;

	return choice;
}

void print(int& i){
	cout<<i<<"\n";
}

int main(){

	int nVertices;
	char mode;
	int src, dest;


	cout<<"Enter no. of vertices : ";
	cin>>nVertices;
	
	cout<<"Enter mode of implementation(m: Adjacency matrix | l: Adjacency list) : ";
	cin>>mode;

	UndirectedGraph graph(nVertices, mode);

	while(1){
		try{
			switch(options()){

				case 1 :	cout<<"Enter source : ";
							cin>>src;
							cout<<"Enter destination : ";
							cin>>dest;

							graph.add(src, dest);
						
							break;

				case 2 :	cout<<"Enter source : ";
							cin>>src;
							cout<<"Enter destination : ";
							cin>>dest;

							graph.remove(src, dest);
							
							break;

				case 3 :	cout<<"Enter source : ";
							cin>>src;
							cout<<"Enter destination : ";
							cin>>dest;

							if(graph.edgeExists(src, dest))
								cout<<"Edge exists.";
							else
								cout<<"Edge does not exists.";
						
							break;

				case 4 :	cout<<"Enter vertex : ";
							cin>>src;

							cout<<"Degree["<<src<<"] : "<<graph.degree(src);
							break;

				case 5 :	cout<<graph.vertices();
							break;

				case 6 :	cout<<graph.edges();
							break;

				case 7 :	graph.dfs(print);
							break;

				case 8 :	graph.bfs(print);
							break;

				case 0 :	exit(EXIT_SUCCESS);

				default :	cout<<"Invalid Choice.";

			}
		}
		catch(const char* err){
			cout<<err<<endl;
		}
	}

	return 0;
}