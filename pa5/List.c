//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 6/9/18
// List.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"


// private types --------------------------------------------------------------

// NodeObj
typedef struct NodeObj{
   int vertex;
   struct NodeObj* next;
   struct NodeObj* before;
} NodeObj;


// Node
typedef NodeObj* Node;


// newNode()
// constructor of the Node type
Node newNode(int x) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
  
   N->vertex = x;
   N->next = NULL;
   N->before = NULL;
   
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// ListObj
typedef struct ListObj{
   Node head;
   Node tail;
   int numItems;
   Node cursor;
   int index;
} ListObj;

// constructor - destructor ---------------------------------------------

// newDictionary()
// constructor for the Stack type
List newList(void){
   List L = malloc(sizeof(ListObj));
   assert(L!=NULL);
   
   L->head = NULL;
   L->tail = NULL;
   L->numItems = 0;
   L->cursor = NULL;
   L->index = -1;
   
   return L;
}

// freeDictionary()
// destructor for the Dictionary type
void freeList(List* pL){
   if( pL!=NULL && *pL!=NULL ){
      if( length(*pL) != 0 ) clear(*pL);
         free(*pL);
      *pL = NULL;
   }
}




// access functions -----------------------------------------------------------

//returns length of List L
int length(List L){
   if( L == NULL ){
      fprintf(stderr, 
         "List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return L->numItems;
}


int index(List L){
   if( L == NULL ){
      fprintf(stderr, 
         "List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->index);
}


int front(List L){
   if( L == NULL ){
      fprintf(stderr, 
         "List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0){
      fprintf(stderr,
         "List Error: calling front() on empty List\n");
      exit(EXIT_FAILURE);
   }
   return L->head->vertex;
}


int back(List L){
   if( L == NULL ){
      fprintf(stderr, 
         "List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0){
      fprintf(stderr,
         "List Error: calling back() on empty List\n");
      exit(EXIT_FAILURE);
   }
   return L->tail->vertex;
}


int get(List L){
   if( L == NULL ){
      fprintf(stderr, 
         "List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL){
      fprintf(stderr,
         "List Error: calling get() on null cursor reference\n");
      exit(EXIT_FAILURE);
   }
   return L->cursor->vertex;
}


int equals(List A, List B){
   Node N;
   Node M;
   //error message
   if( A == NULL || B == NULL){
      fprintf(stderr, 
         "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (length(A) != length(B)){
      return 0; //length not the same
   }
   for(N = A->head, M = B->head; N != NULL && M!=NULL; N=N->next, M=M->next){
      if(N->vertex != M->vertex){
         return 0;
      }
   }
   return 1;
}


// Manipulation Procedures----------------------------------------------


// resets this list to its original empty state.
void clear(List L){
   Node N;
   Node temp;

   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   N = L->head;
   while(N != NULL){
      temp = N;
      N=N->next;
      freeNode(&temp);
   }

   L->numItems = 0;
   L->head = NULL;
   L->tail = NULL;
   L->cursor = NULL;
   L->index = -1;

}



// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if(length(L) != 0){
      L->cursor = L->head;
      L->index = 0;
   }
}

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if(length(L) != 0){
      L->cursor = L->tail;
      L->index = L->numItems - 1;
   }
}

// If cursor is defined and not at front, moves cursor one step toward 
// front of this List, if cursor is defined and at front, cursor becomes 
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if(L->cursor != NULL){
      L->cursor = L->cursor->before;
      L->index--;
      if(L->cursor == NULL){ L->index = -1; }   
   }

}

// If cursor is defined and not at back, moves cursor one step toward 
// back of this List, if cursor is defined and at back, cursor becomes 
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if(L->cursor != NULL){
      L->cursor = L->cursor->next;
      L->index++;
      if(L->cursor == NULL) { L->index = -1; }
   }

}

// insert new element into this list. if list is non-empty,
//insertion takes place before front element.
void prepend(List L, int vertex){
   Node N = newNode(vertex);
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if( L-> numItems == 0){
      L->head = N;
      L->tail = N;
      L->numItems++;
      L->index++;
   } else {
      L->head->before = N;
      N->next = L->head;
      L->head = N;
      L->numItems++;
      L->index++;
   }
}


//insert new element into this list. if list is non-empty,
//insertion takes place after back element.
void append(List L, int vertex){
   Node N = newNode(vertex);
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (L->numItems == 0){
      L->head = N;
      L->tail = N;
      L->numItems++;
   } else {
      L->tail->next = N;
      N->before = L->tail;
      L->tail = N;
      L->numItems++;
   }
}


// insert new element before cursor.
// pre: length() > 0, index() >=0
void insertBefore(List L, int vertex){
   Node N;

   //error
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   //method
   if( length(L) == 0 ){
      prepend(L, vertex);
   } else if (L->cursor == L->head){
      prepend(L, vertex);
   } else{
      N = newNode(vertex);
      L->cursor->before->next = N;
      N->before = L->cursor->before;
      N->next = L->cursor;
      L->cursor->before = N;
      L->numItems++;
      L->index++;
   }
}


//insert new element after cursor.
//pre: length () > 0, index >=0
void insertAfter(List L, int vertex){
   Node N;
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if( length(L) == 0 ){
      append(L, vertex);
   } else if (L->cursor == L->tail){
      append(L, vertex);
   } else { 
      N = newNode(vertex);
      N->before = L->cursor;
      N->next = L->cursor->next;
      L->cursor->next->before = N;
      L->cursor->next = N;
      L->numItems++;
   }


}


//deletes the front element.
//pre length() >0
void deleteFront(List L){
   Node D = L->head;
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if(length(L) == 1){
      clear(L);
   } else if (length(L) > 1){
      L->head->next->before = NULL;
      L->head = L->head->next;
      L->numItems--;
      L->index--;
      freeNode(&D);
   }
   
}


//deletes the back element
//pre length()>0
void deleteBack(List L){
   Node D = L->tail;
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) ==1 ) {
      clear(L);
   } else {
      if (L->tail == L->cursor) { 
         L->cursor = NULL;
         L->index = -1;  
      }
      L->tail->before->next = NULL;
      L->tail = L->tail->before;
      L->numItems--;
      freeNode(&D);
   }

}


//deletes cursor element, making cursor undefined.
// pre: length()>0, index() >=0
void delete(List L){
   Node D = L->cursor;
   if( L == NULL){
      fprintf(stderr, 
         "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (length(L) == 1){
      clear(L);
   } else if (L->cursor == L->head) {
      L->cursor->next->before = NULL;
      L->head = L->cursor->next;
      L->cursor = NULL;
      L->numItems--;
      L->index = -1;
   } else if (L->cursor == L->tail){
      L->cursor->before->next = NULL;
      L->tail = L->cursor->before;
      L->cursor = NULL;
      L->numItems--;
      L->index = -1;
   }
   freeNode(&D);
}


// Other Methods -----------------------------------------------------------


void printList(FILE* out, List L){
   Node N;
   if ( L==NULL){
      fprintf(stderr,
         "List Error: calling printList() on NULL List reference");
      exit(EXIT_FAILURE);
   }
   for(N=L->head; N!=NULL; N=N->next){
      fprintf(out, " %d", (N->vertex));
   }
   fprintf(out, "\n");
}




// Returns a new List representing the same integer sequence as this 
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
   List copy = newList(); 
   for (Node N = L->head; N != NULL; N=N->next){
      append(copy, (N->vertex));
   }
   return copy;
}





















