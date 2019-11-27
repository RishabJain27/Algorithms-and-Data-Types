////Rishab Jain,pa5,rjain9,12/1/17,cmps101
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

//Structs
typedef struct GraphObj{
   List* neighbor;
   char* color;
   int* parent;
   int* discover;
   int* finish;


   int order;
   int size;
   int time;
 
} GraphObj;

//Constructor
Graph newGraph(int n){
	Graph L;
	L = malloc(sizeof(GraphObj));

	L->neighbor = calloc(n+1,sizeof(List));
	L->color = calloc(n+1,sizeof(char));
	L->parent = calloc(n+1,sizeof(int));

	L->discover = calloc(n+1,sizeof(int));
	L->finish = calloc(n+1,sizeof(int));

	for(int i=1;i<=n;i++){
		L->neighbor[i] = newList();
		L->color[i] = 'w';
		L->parent[i] = NIL;
		L->discover[i] = UNDEF;
		L->finish[i] = UNDEF;
	}

	L->order = n;
	L->size = 0;
	L->time = 0;

	return(L);
}
//Destructor
void freeGraph(Graph* pG){
	for (int i=1; i<=getOrder(*pG);i++){
		freeList(&(*pG)->neighbor[i]);
	}
	
	free((*pG)->neighbor);
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->discover);
	free((*pG)->finish);

	free(*pG);
	pG = NULL;
}

/*** Access functions ***/

int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(1);
	}
	else{
		return G->order;
	}
}
int getSize(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	else{
		return G->size;
	}
}
int getParent(Graph G, int u){
	if(u < 1 || u>getOrder(G)){
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(1);
	}
	else{
		return G->parent[u];
	}
}
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
	if(u<1 || u>getOrder(G)){
		printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
		exit(1);
	}
	else{
		return G->discover[u];
	}
}
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
	if(u<1 || u>getOrder(G)){
		printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
		exit(1);
	}
	else{
		return G->finish[u];
	}
}

/* Manipulation procedures */

void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(1);
	}
	
	addArc(G,u,v);
	addArc(G,v,u);

	G->size--;
}
void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(1);
	}

	moveFront(G->neighbor[u]);

	while(index(G->neighbor[u]) != -1 && v>get(G->neighbor[u])){
		moveNext(G->neighbor[u]);
	}
	
	if(index(G->neighbor[u]) == -1){
		append(G->neighbor[u],v);
	}
	else{
		insertBefore(G->neighbor[u],v);
	}

	G->size++;
}

/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S){
	if (length(S) != getOrder(G)){
		printf("Graph Error: calling DFS() on NULL Graph reference\n");
		exit(1);
	}
	int i = 1;
	moveFront(S);
	while(index(S) != -1){
		G->color[i] = 'w';
		G->parent[i] = NIL;
		i++;
		moveNext(S);
	}
	G->time = 0;
	moveFront(S);
	while(index(S) != -1){
		if(G->color[get(S)] == 'w'){
			visit(G,S,get(S));
		}
		moveNext(S);
	}

	for(int i=1;i<=getOrder(G);i++){
		deleteBack(S);
	}
}

void visit(Graph G,List S,int u){
	G->time = G->time + 1;
	G->discover[u] = G->time;
	G->color[u] = 'g';
	moveFront(G->neighbor[u]);
	while(index(G->neighbor[u]) != -1){
		if(G->color[get(G->neighbor[u])] == 'w'){
			G->parent[get(G->neighbor[u])] = u;
			visit(G,S,get(G->neighbor[u]));
		}
		moveNext(G->neighbor[u]);
	}

	G->color[u] = 'b';
	G->time = G->time + 1;
	G->finish[u] = G->time;
	prepend(S,u);

}

Graph transpose(Graph G){
	if(G == NULL){
		printf("Graph Error: calling transpose() on NULL Graph reference\n");
		exit(1);
	}
	Graph temp = newGraph(getOrder(G));

	for(int i=1;i<=getOrder(G);i++){
		List s = G->neighbor[i];
		moveFront(s);
		while(index(s) != -1){
			append(temp->neighbor[get(s)],i);
			moveNext(s);
		}
	}
	return temp;
}
/*** Other operations ***/

Graph copyGraph(Graph G){
	Graph temp = newGraph(G->order);

	for(int i=1; i<=G->order;i++){
		temp->color[i] = G->color[i];
		temp->parent[i] = G->parent[i];
		temp->discover[i] = G->discover[i];
		temp->finish[i] = G->finish[i];
		temp->neighbor[i] = copyList(G->neighbor[i]);

		temp->order = G->order;
		temp->size = G->size;
	}

	return temp;
}
void printGraph(FILE* out, Graph G){
	for(int i=1;i<=G->order;i++){
    	fprintf(out, "%d:", i);
    	
    	moveFront(G->neighbor[i]);
    	while(index(G->neighbor[i]) != -1){
        	fprintf(out," %d",get(G->neighbor[i]));
        	moveNext(G->neighbor[i]);
        }

    	fprintf(out,"\n");
   }
}





