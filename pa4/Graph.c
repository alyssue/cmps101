//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 5/29/18
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
   int source;       //most recent source used for BFS
   int order;        //number of vertices
   int size;         //number of edges
   int *color;       //color[i] = color of vertex i
   int *parent;      //parent[i] = parent of the vertex i
   int *distance;    // distance[i] = distance from the (most recent) source to vertex i
   List *neighbor;   //neighbor[i] = list of neighbors of vertex i
} GraphObj;


// Graph
typedef GraphObj* Graph;


// newGraph()
// constructor for the Stack type
Graph newGraph (int n){
   int i;
   Graph G = malloc(sizeof(GraphObj));
   assert(G!=NULL);
  
   G->source = NIL;
   G->order = n;
   G->size = 0;
   G->color = malloc(sizeof(int)*(n+2));
   G->parent = malloc(sizeof(int)*(n+2));
   G->distance = malloc(sizeof(int)*(n+2));
   G->neighbor = malloc(sizeof(List)*(n+2));
   assert(G->color != NULL);
   assert(G->parent != NULL);
   assert(G->distance != NULL);
   assert(G->neighbor != NULL);
   for(i = 1; i<= n+1; i++){
      G->color[i] = 1;
      G->parent[i] = NIL;
      G->distance[i] = INF;
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
      free((*pG)->distance);
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


// getSource()
// returns the source used last in BFS.
// if BFS not yet ran, returns NIL
int getSource(Graph G){
   if( G == NULL ){
      fprintf(stderr, 
         "Graph Error: calling getSource() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return G->source;
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



// getDist()
// returns the distance of vertex u from the source of graph G
// pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
   if( G == NULL ){
      fprintf(stderr, 
         "List Error: calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr, 
         "Graph Error: calling getDist() on invalid vertex\n");
      exit(EXIT_FAILURE);
   }
   return G->distance[u];
}



// getPath()
// prepends the vertexes in order of a shortest path created by BFS from the source to vertex u
// pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
   if( G == NULL ){
      fprintf(stderr, 
         "List Error: calling getPath() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr, 
         "Graph Error: calling getPath() on invalid vertex\n");
      exit(EXIT_FAILURE);
   }
   if(G->source == NIL){
      fprintf(stderr, 
         "Graph Error: calling getPath() before running BFS\n");
      exit(EXIT_FAILURE);
   } 

   if(G->source == u){                 // if the source source is the vertex, 
      append(L, G->source);            // the path is the vertex itself
   } else if (getParent(G, u) == NIL){ // if a vertex leading up the BFS tree is null, 
      append(L, NIL);                  // then no path to s
   } else {  
      getPath(L, G, G->parent[u]);     // climb up tree recursively
      append(L,u);                     // u is last in list 
   }
}





// Manipulation Procedures----------------------------------------------


// makeNull()
// deletes all edges of G, restoring it to its original (no edge) state 
void makeNull(Graph G){
   int i;
   if( G == NULL ){
      fprintf(stderr, 
         "List Error: calling makeNull() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   for(i = 1; i <= getOrder(G); i++){
      G->distance[i] = INF;
      G->parent[i] = NIL; 
      clear(G->neighbor[i]);
   }
   G->size = 0; 
}


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
      prepend(L, v);
      G->size++;
   }
}


// BFS()
// runs the BFS algorithm on the Graph G with source s
// setting the color, distance, parent, and source fields of G accordinly
void BFS(Graph G, int s){
   List Q = newList();
   int x; // vertex pointing at 
   int y; // neighbors of vertex x
   if( G == NULL ){
      fprintf(stderr, 
      "List Error: calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for(x = 1; x <= getOrder(G); x++){
      G->color[x] = 1; //white
      G->distance[x] = INF;
      G->parent[x] = NIL;
   }
   G->source = s;
   G->color[s] = 2; //grey
   G->distance[s] = 0;
   G->parent[s] = NIL;
   append(Q, s); //enqueue(Q, s)
  
   while(length(Q) >= 1){  // while Q is not empty
      x = front(Q);        // get vertex that's at front of queue.
      deleteFront(Q);      // pop Q

      //for all adjacent vertices, if any
      if(length(G->neighbor[x]) > 0){
         moveFront(G->neighbor[x]);
         y = NIL;
         while(index(G->neighbor[x]) >= 0){
            y = get(G->neighbor[x]);   //for this neighbor,

            if(G->color[y] == 1){      //if not discovered yet
               G->color[y] = 2;        //discover it
               G->distance[y] = G->distance[x]+1; //mark its distance
               G->parent[y] = x;       //assign it's parent
               append(Q, y);           //push onto Queue
            }
            moveNext(G->neighbor[x]); //go to next neighbor
         }
      }                 // after all neighbors
      G->color[x] = 3;  //color x black, go to next vertex in Queue.
   }
   freeList(&Q);
}
   


// Other Methods -----------------------------------------------------------


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
















