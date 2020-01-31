//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 6/9/18
// FindComponents.c
//
// To find the strong components of a digraph G call DFS(G). 
// As vertices are finished, place them on a stack.
// When DFS is complete the stack stores the vertices ordered by decreasing finish times. 
// Next compute the transpose G^T of G. 
// (The digraph G^T is obtained by reversing the directions on all edges of G.) 
// Finally run DFS(G^T), but in the main loop (lines 5-7) of DFS, 
// process vertices in order of decreasing finish times from the first call to DFS. 
// This is accomplished by popping vertices off the stack. 
// When the whole process is complete, the trees in the resulting DFS forest span the strong components of G. 
// Note that the strong components of G are identical to the strong components of G^T. 
// See the algorithm Strongly-ConnectedComponents and proof of correctness in section 22.5 of the text.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<assert.h>
#include"Graph.h"
#include"List.h"
#define INF (-1) //infinity = -100
#define NIL (0)  //undefined vertex label = -1


// HELPER FUNCTIONS ------------------------------------------------------------------

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


// MAIN ----------------------------------------------------------------------------

int main(int argc, char* argv[]){
	FILE* in; 
	FILE* out;
	int i = 0;
	int x = 0;
	int numSCC;
	List *SCC;
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

	// input data Group 1-----------------------------------------------------------------
	fscanf(in, "%d", &i);
	Graph G = newGraph(i);
	for(int n = 1; n <= i; n++){
		append(L, n);
	}

	while (1) {  
		fscanf (in, "%d", &i);
		fscanf (in, "%d", &x);
		if((i == 0) & (x == 0)){
			break;
		}
		addArc(G, i, x); 
	}

	//-print the adjacency list representation of the graph to the output file-----------------
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);


	//-FindComponents---------------------------------------------------------------------------

	// Run DFS on G and GT, processing the vertices in the second call 
	// by decreasing finish times from the first call.
	DFS(G, L);
	Graph GT = transpose(G);
	DFS(GT, L);

	// get the number of strongly connected components
	moveFront(L);
	numSCC = 0; //
	while(index(L) >= 0){
		if(getParent(GT, get(L)) == NIL){
			numSCC++;
		}
		moveNext(L);
	}


	// Array of Lists, each list holds vertices in a SCC
	SCC = malloc(sizeof(List)*(numSCC+1)); 
	assert(SCC != NULL);


	// Put vertices into the array indexes
	moveBack(L); //start at back of List
	while(index(L) >= 0){
		for(int i = 1; i <= numSCC; i++){
			SCC[i] = newList();
			while(getParent(GT, get(L)) != NIL){
				prepend(SCC[i], get(L));
				movePrev(L);
			}
			prepend(SCC[i], get(L));
			movePrev(L);		
		}
	}
	


	// print those bitches
	fprintf(out, "\n");
	fprintf(out, "G contains %d strongly connected components:\n", numSCC);

	for(int i = 1; i <= numSCC; i++){
		fprintf(out, "Component %d:", i);
		printList(out, SCC[i]);
	}


	//-Free Memory--------------------------------------------------------------------------------

	//freeList(SCC);
	freeGraph(&G);


	//-close input and output files-------------------------------------------------------------
	fclose(in);
	fclose(out);

	return(EXIT_SUCCESS);
}