//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 6/9/18
// Graph.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Graph.h"


//-GRAPH-STUFF------------------------------------------------------------------

// GraphObj
typedef struct GraphObj{
   int order;        // number of vertices
   int size;         // number of edges
   int *color;       // color of vertex;
   int *parent;      // parent[i] = parent of the vertex i
   int *discover;    // discover[i] = discover time from the (most recent) call to DFS
   int *finish;      // finish[i] = finish time from the (most recent) call to DFS
   List *neighbor;   // neighbor[i] = list of neighbors of vertex i
} GraphObj;


// Graph
typedef GraphObj* Graph;


// newGraph()
// constructor for the Stack type
Graph newGraph (int n){
   int i;
   Graph G = malloc(sizeof(GraphObj));
   assert(G!=NULL);
  
   G->order = n;
   G->size = 0;
   G->color = malloc(sizeof(int)*(n+2));
   G->parent = malloc(sizeof(int)*(n+2));
   G->discover = malloc(sizeof(int)*(n+2));
   G->finish = malloc(sizeof(int)*(n+2));
   G->neighbor = malloc(sizeof(List)*(n+2));
   assert(G->color != NULL);
   assert(G->parent != NULL);
   assert(G->discover != NULL);
   assert(G->neighbor != NULL);
   for(i = 1; i < n+2; i++){
      G->color[i] = 1;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
      G->neighbor[i] = newList();
   }
   return G;
}


// freeGraph()
// destructor for the Graph type
void freeGraph(Graph* pG){
   if( pG!=NULL && *pG!=NULL ){
      free((*pG)->color);
      free((*pG)->parent);
      free((*pG)->discover);
      free((*pG)->finish);
      for(int i = 1; i < getOrder(*pG)+2; i++){
         freeList(&((*pG)->neighbor[i]));
      }
      free((*pG)->neighbor);
      free(*pG);
      *pG = NULL;
   }
}


//-ACCESS-FUNCTIONS-----------------------------------------------------------

// getOrder()
// returns the number of vertices in graph G
int getOrder(Graph G){
   if( G == NULL ){
      fprintf(stderr, 
         "List Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}


// getSize()
// returns the number of edges in graph G
int getSize(Graph G){
   if( G == NULL ){
      fprintf(stderr, 
         "Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}


// getParent()
// returns parent to vertex u in Graph G
// pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
   if( G == NULL ){
      fprintf(stderr, 
         "Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } 
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr, 
         "Graph Error: calling getParent() on invalid vertex\n");
      exit(EXIT_FAILURE);
   }
   return G->parent[u];
}

// getDiscover
// Pre: 1<=u<=n=getOrder(G) 
int getDiscover(Graph G, int u){
   if( G == NULL ){
      fprintf(stderr, 
         "Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } 
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr, 
         "Graph Error: calling getDiscover() on invalid vertex\n");
      exit(EXIT_FAILURE);
   }
   return G->discover[u];
}




// getFinish()
// Pre: 1<=u<=n=getOrder(G) 
int getFinish(Graph G, int u){
   if( G == NULL ){
      fprintf(stderr, 
         "Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } 
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr, 
         "Graph Error: calling getFinish() on invalid vertex\n");
      exit(EXIT_FAILURE);
   }
   return G->finish[u];
}




// Manipulation Procedures----------------------------------------------


// addEdge()
// inserts a new edge joining u to v:
// u is added to the adjacency List of v, and 
// v to the adjacency List of u
// maintain these lists in sorted order by increasing labels
void addEdge(Graph G, int u, int v){
   if( G == NULL ){
      fprintf(stderr, 
         "List Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}


// addArc()
// inserts a new directed edge from u to v
// i.e. v is added to the adjacency List of u 
// (but not u to the adjacency list of v)
void addArc(Graph G, int u, int v){
   List L;
   if( G == NULL ){
      fprintf(stderr, 
         "List Error: calling addArc() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   //add v to adjacency list of u
   L = G->neighbor[u];
   moveFront(L);              // begin at beginning of list
   
   while(index(L) >= 0){
      if(get(L) > v){
         insertBefore(L, v);
         G->size++;
         break;
      } else {
         moveNext(L);
      }
   }
   if(index(L) == -1){
      append(L, v);
      G->size++;
   }
}


// visit() helper function to DFS
void visit(Graph G, int x, int *t, List L){
   int y;
   G->color[x] = 2; //discover
   G->discover[x] = ++(*t); //discover time
   moveFront(G->neighbor[x]); //start looking at all neighbors of this vertex
   while(index(G->neighbor[x]) >= 0){ // for all the neighbors
      y = get(G->neighbor[x]); //get the vertex number
      if(G->color[y] == 1){ //if its undiscovered
         G->parent[y] = x; //then it's parent is x
         visit(G, y, t, L); //then visit it
      }
      moveNext(G->neighbor[x]); //go to next neighbor
   }
   G->color[x] = 3; //then it's finished
   G->finish[x] = ++(*t); //finish time
   insertAfter(L, x);
}


// Pre: length(S)==getOrder(G) 
void DFS(Graph G, List L){
   if( G == NULL ){
      fprintf(stderr, 
         "Graph Error: calling DFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( L == NULL ){
      fprintf(stderr, 
         "Graph Error: calling DFS() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }   
   if( length(L) != getOrder(G) ){
      fprintf(stderr, 
         "List Error: calling DFS() with Stack of improper size\n");
      exit(EXIT_FAILURE);
   }

   //reset all fields
   for(int i = 1; i <= getOrder(G); i++){
      G->color[i] = 1;
      G->parent[i] = NIL;  
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }

   //create time counter
   int time = 0; // local time variable 
   int *t = NULL; // pointer
   t = &time; // pointer points to time variable.


   moveBack(L); //put cursor on final element
   while(index(L) >= 0){ //until the cursor gets deleted 
      int x = front(L); 
      if(G->color[x] == 1) visit(G, x, t, L); //if undiscovered, visit
      deleteFront(L); 
   }
}



// Other Methods -----------------------------------------------------------

// transpose()
// reverse all directed edges
Graph transpose(Graph A){
   Graph G = newGraph(getOrder(A));
   int i, j;
   if( A == NULL ){
      fprintf(stderr, 
         "List Error: calling transpose() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for ( i = 1; i < getOrder(A)+1; i++){
      moveFront(A->neighbor[i]);
      while(index(A->neighbor[i]) >= 0){
         j = get(A->neighbor[i]); 
         addArc(G, j, i);
         moveNext(A->neighbor[i]);
      }
   }
   return G;
}


// copyGraph()
Graph copyGraph(Graph A){
   Graph G;
   int n, i;
   if( A == NULL ){
      fprintf(stderr, 
         "List Error: calling copyGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   n = getOrder(A);

   G = malloc(sizeof(GraphObj));
   assert(G!=NULL);
  
   G->order = n;
   G->size = A->size;
   G->color = malloc(sizeof(int)*(n+2));
   G->parent = malloc(sizeof(int)*(n+2));
   G->discover = malloc(sizeof(int)*(n+2));
   G->finish = malloc(sizeof(int)*(n+2));
   G->neighbor = malloc(sizeof(List)*(n+2));
   assert(G->color != NULL);
   assert(G->parent != NULL);
   assert(G->discover != NULL);
   assert(G->finish != NULL);
   assert(G->neighbor != NULL);
   for(i = 1; i<= n+2; i++){
      G->color[i] = A->color[i];
      G->parent[i] = A->parent[i];
      G->discover[i] = A->discover[i];
      G->finish[i] = A->discover[i];
      G->neighbor[i] = copyList(A->neighbor[i]);
   }
   return G;
}


// printGraph()
// prints the adjacency list representation of G to the file pointed to by out
// the format of this representation should match the above examples,
// so all that is required by the client is a single call to printGraph()
void printGraph(FILE* out, Graph G){
   int i;
   if ( G==NULL){
      fprintf(stderr,
         "List Error: calling printGraph() on NULL Graph reference");
      exit(EXIT_FAILURE);
   }
   for (i = 1; i <= getOrder(G); i++){
      fprintf(out, "%d:", i);
      printList(out, G->neighbor[i]);
   }
}
















