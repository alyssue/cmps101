//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 4/23/18
// Lex.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"List.h"

	int main(int argc, char* argv[]){
	FILE* in; 
	FILE* out;
	char* *lines;
	char line[300];
	List L = newList();
	int lineCount = 0;
	int i = 0;
	int x = 0;


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


	// count the number of lines in file
	while(fgets(line, sizeof(line), in) != NULL){
		lineCount++;
	}
	rewind(in); //go back to beginning of file

	lines = malloc(lineCount*sizeof(char *));

	// put lines into array
	while(fgets(line, sizeof(line), in) != NULL){
		lines[x] = malloc(strlen(line));
		strcpy(lines[x], line);
		printf("%s\n", lines[x]);
		x++;
	}


	//printf("before put input lines into array\n");
	fgets(*lines, 300, in);

	//printf("after put lines into array\n");

	// -------------------------------------------------------------------

	append(L, 0);


	// do insertion sort w/ List methods
	for(i = 1; i<lineCount; i++){          
		moveBack(L);                                // begin at end of list
		while( index(L) >= 0 ){                        // not off edge of list
			if ((strcmp(lines[i], lines[get(L)])) < 0){    // compare
				movePrev(L);                          // decrement
			} else { 
				insertAfter(L, i);                      // insert after
				break;                                 // no reason to continue loop
			}
		}  
		if(index(L) == -1){                         // if go off end, then belongs at beginning of list
			prepend(L, i);
		}                                            
	}     

	//-Print Elements in Order---------------------------------------------------------------------
	printf("print elements in order\n");

	moveFront(L);
	while(index(L) != -1){
		x = get(L);
		fprintf(out, "%s\n", lines[x]);
		moveNext(L);
	}



	//-Free Memory--------------------------------------------------------------------------------

	clear(L);
	free(L);
	for(i=0; i<lineCount; i++){
		free(lines[i]);
		lines[i] = NULL;
	} 
	free(lines);
	lines = NULL;






	//-close input and output files-------------------------------------------------------------
	fclose(in);
	fclose(out);

	return(EXIT_SUCCESS);
}