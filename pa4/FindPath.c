//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 5/29/18
// FindPath.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"Graph.h"
#include"List.h"
#define INF (-1) //infinity = -100
#define NIL (0)  //undefined vertex label = -1


void printPath(FILE* out, Graph G, int i, int x){
	if(i == x){
		fprintf(out, "%d", i);
	} else if (getParent(G, x) == NIL){
		fprintf(out, "No %d-%d path exists\n", i, x);
	} else {
		printPath(out, G, i, getParent(G, x));
		fprintf(out, " %d", x);
	}
}

int main(int argc, char* argv[]){
	FILE* in; 
	FILE* out;
	int i = 0;
	int x = 0;
	List L = newList();


	// check command line for correct number of arguments
	if( argc != 3 ){
	printf("Usage: %s <input file> <output file>\n", argv[0]);
	exit(EXIT_FAILURE);
	}


	// open input file for reading
	in = fopen(argv[1], "r");
	if( in==NULL ){
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}


	// open output file for writing 
	out = fopen(argv[2], "w");
	if( out==NULL ){
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	// input data Group 1---------------------------------------------------------
	fscanf(in, "%d", &i);
	Graph G = newGraph(i);

	while (1) {  
		fscanf (in, "%d", &i);
		fscanf (in, "%d", &x);
		if((i == 0) & (x == 0)){
			break;
		}
		addEdge(G, i, x);
	}

	// print the adjacency list representation of the graph to the output file.
	printGraph(out, G);

	// input data Group 2----------------------------------------------------------
	while (1) {  
		fscanf (in, "%d", &i);
		fscanf (in, "%d", &x);
		if((i == 0) && (x == 0)){
			break;
		}
		//run BFS on the source vertex, 
		BFS(G, i);
		clear(L);
		getPath(L, G, x);
		if(getDist(G, x) == -1){
			//print the distance to the destination vertex, 
			fprintf(out, "\n\nThe distance from %d to %d is infinity\n", i, x);


			// print a message if no path from source to destination exists 
			fprintf(out, "No %d-%d path exists", i, x);

		} else {

			//print the distance to the destination vertex, 
			fprintf(out, "\n\nThe distance from %d to %d is %d", i, x, getDist(G, x));
			fprintf(out, "\n");

			//if it exists, find and print the resulting shortest path
			fprintf(out, "A shortest %d-%d path is: ", i, x);
			printPath(out, G, i, x);

		}
	}



	//-Free Memory--------------------------------------------------------------------------------

	freeGraph(&G);


	//-close input and output files-------------------------------------------------------------
	fclose(in);
	fclose(out);

	return(EXIT_SUCCESS);
}