/*  Author : Indresh Kumar Gupta
    Purpose : Algorithm to solve flood fill problem using matrix traversal (using DFS)
    Version : 1.3

*/

#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

void print(int**& matrix, int m, int n){

	for(int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			
			if(matrix[i][j] == 2)
				cout<<"P ";
			
			if(matrix[i][j] == 1)
				cout<<"X ";

			if(matrix[i][j] == 0)
				cout<<"O ";
		}
		cout<<endl;
	}
}

bool floodfill(int**& matrix, int m, int n, int srcr, int srcc, int destr, int destc){

	static bool print = false, change = false;
	if(srcc < 0 || srcc >= n || srcr < 0 || srcr >= m)
		return false;

	if(destc < 0 || destc >= n || destr < 0 || destr >= m)
		return false;	

	if(matrix[srcr][srcc] == 1 || matrix[srcr][srcc] == 2){
		print = true;
		return false;
	}
	else
		matrix[srcr][srcc] = 2;

	print = false;

	cout<<"Move to ("<<srcr<<","<<srcc<<")\n";

	int n_srcr, n_srcc, pos = 0, counter = 0, flag[8];

	for(int i = 0; i < 8; i++)
		flag[i] = 0;

	if(srcr == destr && srcc == destc)
		return true;	
	
	while(counter < 8){

		srand(time(NULL));
		pos = rand() % 8;

		while(flag[pos] == 1)
			pos = rand() % 8;

		flag[pos] = 1;
		counter++;

		switch(pos){
			case 0:	n_srcr = srcr - 1;
					n_srcc = srcc - 1;
					break;

			case 1:	n_srcr = srcr - 1;
					n_srcc = srcc;
					break;

			case 2:	n_srcr = srcr - 1;
					n_srcc = srcc + 1;
					break;
			
			case 3:	n_srcc = srcc - 1;
					n_srcr = srcr;
					break;
			
			case 4:	n_srcc = srcc + 1;
					n_srcr = srcr;
					break;
			
			case 5:	n_srcr = srcr + 1;
					n_srcc = srcc - 1;
					break;
			
			case 6:	n_srcr = srcr + 1;
					n_srcc = srcc;
					break;

			case 7:	n_srcr = srcr + 1;
					n_srcc = srcc + 1;
					break;
		}

		if(floodfill(matrix, m, n, n_srcr, n_srcc, destr, destc))
			return true;


		if(print && change){
			cout<<"Move to ("<<srcr<<","<<srcc<<")\n";
			change = false;
		}

	}

	if(print && change){
		cout<<"Move to ("<<srcr<<","<<srcc<<")\n";
	}

	change = true;

	return false;
}

int main(){

	int m, n;
	cout<<"Enter m  and n : ";
	cin>>m>>n;

	int** matrix;
	matrix = new int*[m];
	for(int i = 0; i < m; i++){
		matrix[i] = new int[n];
		for(int j = 0; j < n; j++)
			matrix[i][j] = 0;
	}

	int srcr, srcc, destr, destc, nInvalid;
	
	cout<<"No. of unvisitable nodes : ";
	cin>>nInvalid;

	cout<<"Details of unvisitable nodes\n";
	for(int i = 0; i < nInvalid; i++){
		cout<<"Enter coordinates : ";
		cin>>srcr>>srcc;

		if(srcr >= 0 and srcr < m and srcc >=0 and srcc < n)
			matrix[srcr][srcc] = 1;
	}


	cout<<"Source coordinates : ";
	cin>>srcr>>srcc;

	cout<<"Destination coordinates : ";
	cin>>destr>>destc;

	cout<<"\nPath traversed :\n";
	if(floodfill(matrix, m, n, srcr, srcc, destr, destc)){
		cout<<"Destination can be reached.\n\n";
		print(matrix, m, n);
	}
	else
		cout<<"Destination can't be reached.\n";

	return 0;
}