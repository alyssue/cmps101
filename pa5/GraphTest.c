//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 6/9/18
// GraphTest.c

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
#include"Graph.h"
#include"List.h"
#define INF (-1) //infinity = -100
#define NIL (0)  //undefined vertex label = -1


// MAIN ----------------------------------------------------------------------------

int main(int argc, char* argv[]){
   FILE* in; 
   FILE* out;
   int i = 0;
   int x = 0;
   int numSCC;
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


//-TESTS--------------------------------------------------------------------------------------

   // Initial Composition of Graph G and List L

   // ORDER G
   fprintf(out, "\n");
   fprintf(out, "Order of G is: %d\n", getOrder(G));
   fprintf(out, "\n");

   // List L 1-Order
   fprintf(out, "The initial List L is:\n");
   printList(out, L);
   fprintf(out, "\n");

   //-DFS CALL ONE----------------------------------------------------------------------------------


   fprintf(out, "\n");
   fprintf(out, "//-DFS CALL ONE---------------------------------------------------------------------------------- \n");
   fprintf(out, "\n");
   
   List J = copyList(L);
   DFS(G,L); // 1

   moveFront(J);
   // PRINT DISOVER, FINISH, AND PARENT
   for(int i = 1; i <= getOrder(G); i++){
      int n = get(J);
      fprintf(out, "The discover of vertex %d is: %d\n", n, getDiscover(G, n));
      fprintf(out, "The finish of vertex %d is: %d\n", n, getFinish(G, n));
      fprintf(out, "The parent of vertex %d is: %d\n", n, getParent(G, n));
      fprintf(out, "\n");
      moveNext(J);
   }

   // NEW L
   fprintf(out, "The List L after second call to DFS is:\n");
   printList(out, L);


   //-----------------------------------------------------------------------------------

   fprintf(out, "\n");
   fprintf(out, "//-DFS CALL TWO---------------------------------------------------------------------------------- \n");
   fprintf(out, "\n");
   
   J = copyList(L);
   DFS(G,L); // 1

   moveFront(J);
   // PRINT DISOVER, FINISH, AND PARENT
   for(int i = 1; i <= getOrder(G); i++){
      int n = get(J);
      fprintf(out, "The discover of vertex %d is: %d\n", n, getDiscover(G, n));
      fprintf(out, "The finish of vertex %d is: %d\n", n, getFinish(G, n));
      fprintf(out, "The parent of vertex %d is: %d\n", n, getParent(G, n));
      fprintf(out, "\n");
      moveNext(J);
   }

   // NEW L
   fprintf(out, "The List L after second call to DFS is:\n");
   printList(out, L);

   //-----------------------------------------------------------------------------------

   fprintf(out, "\n");
   fprintf(out, "//-TRANPOSE TESTS---------------------------------------------------------------------------------- \n");
   fprintf(out, "\n");

   Graph GT = transpose(G);

   fprintf(out, "Adjacency list representation of GT:\n");
   printGraph(out, GT);

   // ORDER GT
   fprintf(out, "\n");
   fprintf(out, "Order of GT is: %d\n", getOrder(G));
   fprintf(out, "\n");

   // List L 1-Order
   fprintf(out, "The initial List L is:\n");
   printList(out, L);
   fprintf(out, "\n");


   //-DFS GT CALL ONE----------------------------------------------------------------------------------


   fprintf(out, "\n");
   fprintf(out, "//-DFS GT CALL ONE---------------------------------------------------------------------------------- \n");
   fprintf(out, "\n");
   
   J = copyList(L);
   DFS(GT,L); // 1

   moveFront(J);
   // PRINT DISOVER, FINISH, AND PARENT
   for(int i = 1; i <= getOrder(G); i++){
      int n = get(J);
      fprintf(out, "The discover of vertex %d is: %d\n", n, getDiscover(GT, n));
      fprintf(out, "The finish of vertex %d is: %d\n", n, getFinish(GT, n));
      fprintf(out, "The parent of vertex %d is: %d\n", n, getParent(GT, n));
      fprintf(out, "\n");
      moveNext(J);
   }

   // NEW L
   fprintf(out, "The List L after first call to DFS on GT is:\n");
   printList(out, L);


   //-Free Memory--------------------------------------------------------------------------------

   freeGraph(&G);


   //-close input and output files-------------------------------------------------------------
   fclose(in);
   fclose(out);

   return(EXIT_SUCCESS);
}