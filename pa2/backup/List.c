//Rishab Jain,rjain9, pa2, cmps101
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* previous;	
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;

   int indexCursor;
   int lengthList;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->previous = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
    	free(*pN);
    	*pN = NULL;
    }
}

// newQueue()
// Returns reference to new empty Queue object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->lengthList = 0;
   L->indexCursor = -1;
   return(L);
}


// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pQ){
   if(pQ!=NULL && *pQ!=NULL) { 
    	while( length(*pQ) > 0 ) { 
        	deleteFront(*pQ); 
        }
        free(*pQ);
        *pQ = NULL;
   }
}
	
// Access functions
// Returns the number of elements in this List.
int length(List L){
	return L->lengthList;
}

// If cursor is defined, returns the index of the cursor element,// otherwise returns -1.
int index(List L){
	if(L->cursor != NULL){
		return L->indexCursor;
	}
	else {
		return -1;
	}
}
	
// Returns front element. Pre: length()>0
int front(List L) {
	if(length(L) <= 0){
		printf("Queue Error: calling front() on NULL Queue reference\n");
		exit(1);
	}
	else{
		return L->front->data;
	}
}
	
// Returns back element. Pre: length()>0
int back(List L){
	if(length(L) <= 0){
		printf("Queue Error: back() on NULL Queue reference\n");
		exit(1);
	}
	else{
		return L->back->data;
	}
}

// Returns cursor element. Pre: length()>0, index()>=0
int get(List L){
	if(length(L) <= 0 || L->indexCursor < 0){
		printf("Queue Error: calling get() on NULL Queue reference\n");
		exit(1);
	}
	else{
		return L->cursor->data;
	}
}


// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B){
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if(A==NULL || B==NULL){
		printf("List Error: calling equals on NULL reference \n");
		exit(1);
	}
	eq = (A->lengthList == B->lengthList);
	N = A->front;
	M= B->front;
	while(eq && N!=NULL){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	//freeNode(&N);
	//freeNode(&M);
	return eq;
}

// Manipulation procedures
	
// Resets this List to its original empty state.
void clear(List L){	
	if(L == NULL){
	printf("List Error: clear()");
	exit(1);
}
    	
	Node temp = L->front;
	while(temp != NULL){
		Node temp2 = temp->next;
		freeNode(&temp);
		temp = temp2; 
	}
        
        
  	L->lengthList = 0;
	L->indexCursor = -1;
	L->front = L->back = NULL;
	L->cursor = NULL;
   	
}

//If List is non-empty, places the cursor under the front element,otherwise does nothing.
void moveFront(List L){
	if(length(L) > 0){
		L->cursor = L->front;
		L->indexCursor = 0;
	}
}

// If List is non-empty, places the cursor under the back element, otherwise does nothing.
void moveBack(List L){
	if(length(L) >0){
		L->cursor = L->back;
		L->indexCursor = length(L) -1;
	}
}

// If cursor is defined and not at front, moves cursor one step toward 
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
	if(L->cursor != NULL && L->indexCursor != 0){
		L->cursor = L->cursor->previous;
		L->indexCursor--;
	}
	else if( L->cursor != NULL && L->indexCursor == 0){
		L->cursor = NULL;
		L->indexCursor = -1;
	}
	else{
		return;
	}

}


// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
	if(L->cursor != NULL && L->indexCursor != length(L)-1){
		L->cursor = L->cursor->next;
		L->indexCursor++;
	}
	else if(L->cursor != NULL && L->indexCursor == length(L)-1){
		L->cursor = NULL;
		L->indexCursor = -1;
	}
	else{
		return;
	}
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
	Node temp = newNode(data);
		
	if(L->lengthList == 0){
		L->front = temp;
		L->back = temp;
		L->lengthList++;
	}
	else{
		L->front->previous = temp;
		temp->next = L->front;
		//	temp->previous = NULL;
		L->front = temp;
			
		if(L->cursor != NULL){
			L->indexCursor++;
		}
		L->lengthList++;
	}
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
	Node temp = newNode(data);
	if(L->lengthList == 0){
		L->back = temp;
		L->front = temp;
		L->lengthList++;
	}
	else{
		L->back->next = temp;
		temp->previous = L->back;
		//	temp->next = NULL;
		L->back = temp;
		L->lengthList++;
	}
}


// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
	Node temp = newNode(data);
	if(length(L) <= 0 &&  index(L) < 0){
		printf("List Error: calling insertBefore() on NULL List reference\n");
      	exit(1);
	}
	else if(L->cursor == L->front){
		temp->previous = NULL;
		temp->next = L->cursor;
		L->cursor->previous = temp;
		L->front = temp;

		L->indexCursor++;
		L->lengthList++;
	}
	else{
		temp->next = L->cursor;
		temp->previous = L->cursor->previous;
		L->cursor->previous->next = temp;
		L->cursor->previous = temp;

		L->cursor = temp;
		L->indexCursor++;
		L->lengthList++;
	}
}


// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	Node temp = newNode(data);
	if(length(L) <= 0 ||  index(L) < 0){
		printf("List Error: calling insertAfter() on NULL List reference\n");
      	exit(1);
	}
	else if( L->cursor == L->back){
		temp->next = NULL;
		temp->previous = L->cursor;
		L->cursor->next = temp;
		L->back = temp;

		L->lengthList++;
	}
	else{
		temp->previous = L->cursor;
		temp->next = L->cursor->next;
		L->cursor->next->previous = temp;
		L->cursor->next = temp;
		
		L->lengthList++;
	}
}

// Deletes the front element. Pre: length()>0
void deleteFront(List L){
	if(length(L) <= 0){
		printf("List Error: calling printList() on NULL Queue reference\n");
    		 exit(1);
		}
		else if(length(L) == 1){	
			L->indexCursor = -1;
            L->cursor = NULL;
            L->back = NULL;
			
			L->lengthList--;
			freeNode(&L->front);
            // L->back = NULL;
		}
		else{
			L->front = L->front->next;
			//L->front->previous = NULL;
            if(L->cursor == L->front->previous){
                L->cursor = NULL;
            }
			
			L->indexCursor--;
			L->lengthList--;
			
			freeNode(&L->front->previous);
		}
}

// Deletes the back element. Pre: length()>0
void deleteBack(List L){
	if(length(L) <= 0){
		printf("List Error: calling deleteBack() on NULL Queue reference\n");
    	exit(1);
	}
	else if(length(L) == 1){		
		freeNode(&L->back);
        L->front = NULL;
        L->cursor = NULL;
	    L->lengthList=0;
		L->indexCursor= -1;
	}
	else{
		if(L->cursor == L->back){
			L->indexCursor = -1;
		}
		L->back = L->back->previous;
		//L->back->next = NULL;	
		L->lengthList--;	
		freeNode(&L->back->next);
	}
}

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
 	if(length(L) < 0 && index(L) <0){
 		printf("List Error: calling delete() on NULL List reference\n");
      	exit(1);
 	}
 	else if(L->cursor == L->front){
 		deleteFront(L);
 	}
 	else if(L->cursor == L->back){
 		deleteBack(L);
 	}
 	else{
 		L->cursor->next->previous = L->cursor->previous;
 		L->cursor->previous->next = L->cursor->next;
		freeNode(&L->cursor);	
 		
 		L->indexCursor = -1;
 		L->lengthList--;
 	}
}


void printList(FILE* out, List L){
 	Node N = NULL;

    if( L==NULL ){
    	printf("List Error: calling printList() on NULL Queue reference\n");
    	exit(1);
   	}
    	
    for(N = L->front; N != NULL; N = N->next){
      	printf("%d ", N->data);
    }
 }


// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
 	List list = newList();
 	Node temp =NULL;
	if(L == NULL){
		printf("List Error: calling copyList() on empty list");
		exit(1);
	}	
	
	temp = L->front;
 	while( temp != NULL){
 		append(list,temp->data);
 		temp = temp->next;
 	}
 		
 	return list;
}
