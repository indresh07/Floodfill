#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "AdjacencyList.hpp"
#include "stack.hpp"

using namespace std;
using namespace cs202;

int m, n;

enum Color {WHITE, GRAY, BLACK};

void print(int& i){
	cout<<"Move to ("<<(i/n + 1)<<","<<(i%n + 1)<<")\n";
}

bool floodfill(AdjacencyList& matrix, int& src, int& dest, void (*work)(int&)){

  Color color[matrix.vertices()];

  for(int i = 0; i < matrix.vertices(); i++)
    color[i] = WHITE;

  stack<int> dfsStack;

  int i = src, j;
  LinearList<LinearList<int> > adjNodes = matrix.getAdjacent();
  dfsStack.push(src);
  color[src] = GRAY;
  (*work)(src);

    while(!dfsStack.empty()){
       i = dfsStack.top();

      if(adjNodes[i].size() > 0){
      	srand(time(NULL));
      	int pos = rand() % adjNodes[i].size();
        j = adjNodes[i][pos];
        adjNodes[i].erase_pos(pos);
        if(color[j] == WHITE){
          dfsStack.push(j);
          color[j] = GRAY;
          (*work)(j);
          if(j == dest){
          	return true;
          }

        }
      }
      else{
        color[i] = BLACK;
        (*work)(i);
        dfsStack.pop();
      }
    }

    return false;
}

int main(){

	cout<<"Enter m and n : ";
	cin>>m>>n;

	AdjacencyList matrix(m*n);
	LinearList<int> uNodes(m*n);

	int nUNodes;
	cout<<"Enter no. of unvisitable vertices : ";
	cin>>nUNodes;

	int x, y;
	for(int i = 0; i < nUNodes; i++){
		cout<<"["<<i+1<<"] : ";
		cin>>x>>y;
		uNodes.push_back((x-1)*n + y - 1);
	}

	try{
		for(int i = 0; i < m*n; i++){
			if(INT_MAX != uNodes.find(i))
				continue;

			//above left
			if(i > n && (i % n) && INT_MAX == uNodes.find(i - n - 1))
				matrix.add(i, i - n - 1);

			//above
			if(i  >= n && INT_MAX == uNodes.find(i - n))
				matrix.add(i, i - n);

			//above right
			if(i >= n && (i % n != n - 1) && INT_MAX == uNodes.find(i - n + 1))
				matrix.add(i, i - n + 1);

			//left
			if((i % n) && INT_MAX == uNodes.find(i - 1))
				matrix.add(i, i - 1);

			//right
			if((i == 0 || (i % n != n - 1)) && INT_MAX == uNodes.find(i + 1))
				matrix.add(i, i + 1);

			//below left
			if(i < (m-1)*n && (i % n) && INT_MAX == uNodes.find(i + n - 1))
				matrix.add(i, i + n - 1);
			
			//below
			if(i < (m-1)*n && INT_MAX == uNodes.find(i + n))
				matrix.add(i, i + n);

			//below right
			if(i < (m-1)*n && (i == 0 || (i % n != n - 1)) && INT_MAX == uNodes.find(i + n + 1))
				matrix.add(i, i + n + 1);

		}
	}
	catch(const char* err){
		cout<<err<<endl;
		exit(EXIT_SUCCESS);
	}

	matrix.display();

	int src, dest;
	cout<<"Enter source : ";
	cin>>x>>y;

	if( x < 0 || x >= n || y < 0 || y >= m)
		return 0;
	
	src = (x-1)*n + y - 1;

	cout<<"Enter destination : ";
	cin>>x>>y;

	if( x < 0 || x >= n || y < 0 || y >= m)
		return 0;

	dest = (x-1)*n + y - 1;

	if(floodfill(matrix, src, dest, print))
		cout<<"Destination reached\n";
	else
		cout<<"Destination can't be reached.\n";	
	return 0;
}