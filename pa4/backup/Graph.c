////Rishab Jain,pa4,rjain9,11/18/17,cmps101
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

//Structs
typedef struct GraphObj{
   List* neighbor;
   char* color;
   int* parent;
   int* recentDist;

   int order;
   int size;
   int sourceBFS;
} GraphObj;

//Constructor
Graph newGraph(int n){
	Graph L;
	L = malloc(sizeof(GraphObj));

	L->neighbor = calloc(n+1,sizeof(List));
	L->color = calloc(n+1,sizeof(char));
	L->parent = calloc(n+1,sizeof(int));
	L->recentDist = calloc(n+1,sizeof(int));

	for(int i=1; i<=n;i++){
		L->neighbor[i] = newList();
		L->color[i] = 'w';
		L->parent[i] = 0;
		L->recentDist[i] = -1;
	}

	L->order = n;
	L->size = 0;
	L->sourceBFS = 0;

	return(L);
}
//Destructor
void freeGraph(Graph* pG){
	for (int i = 1; i <= getOrder(*pG);i++){
		freeList(& (*pG)->neighbor[i]);
	}
	
	free((*pG)->neighbor);
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->recentDist);

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

int getSource(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
		exit(1);
	}
	else{
		return G->sourceBFS;
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

int getDist(Graph G, int u){
	if(u < 1 || u>getOrder(G)){
        fprintf(stderr, "Graph error: getDist() called on NULL Graph reference\n");
        exit(1);
    }
    else if(getSource(G) == NIL){
    	return INF;
    }
    else{
    	return G->recentDist[u];
    }
}

void getPath(List L, Graph G, int u){
	if(u < 1 || u>getOrder(G)){
        fprintf(stderr, "Graph error: getPath() called on NULL Graph reference\n");
        exit(1);
    }
	else if(getSource(G) == u){
		append(L,u);
	}
	else if(G->parent[u] != NIL){
		getPath(L,G,G->parent[u]);
		append(L,u);
	}
	else{
		append(L,NIL);
	}
}

void makeNull(Graph G){
	if(G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference\n");
		exit(1);
	}
	G->size = 0;
	
	for(int i=1; i<=getOrder(G);i++){
		clear(G->neighbor[i]);
	}
}
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

	while(index(G->neighbor[u]) != -1 && v > get(G->neighbor[u])){
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

void BFS(Graph G, int s){
	for(int i = 0; i < (G->order+1); i++){
		G->color[i] = 'w';
		G->recentDist[i] = INF;
		G->parent[i] = NIL;
	}

	G->color[s] = 'g';
	G->sourceBFS = s;
	G->parent[s] = NIL;
	G->recentDist[s] = NIL;

	List Q = newList();
	append(Q,s);

	while(length(Q) >= 1){
		int u = front(Q);
		deleteFront(Q);

		moveFront(G->neighbor[u]);

		while(index(G->neighbor[u]) != -1){
			if(G->color[get(G->neighbor[u])] == 'w'){
				G->color[get(G->neighbor[u])] = 'g';
				G->recentDist[get(G->neighbor[u])] = G->recentDist[u] + 1;
				G->parent[get(G->neighbor[u])] = u;
				append(Q,get(G->neighbor[u]));
			}
			moveNext(G->neighbor[u]);
		}
		G->color[u] = 'b';
	}
	freeList(&Q); 
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	for (int i = 1; i <= G->order; i++){
    	fprintf(out, "%d:", i);
      
    	moveFront(G->neighbor[i]);

    	while(index(G->neighbor[i]) != -1){
        	fprintf(out," %d",get(G->neighbor[i]));
        	moveNext(G->neighbor[i]);
        }

    	fprintf(out,"\n");
   }
}





