//Rishab Jain,pa5,rjain9,12/1/17,cmps101
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(5);
	List L = newList();
	addArc(G, 1,2);
    addArc(G, 1,5);
    addArc(G, 2,5);
    addArc(G, 2,6);
    addArc(G, 3,2);

    printGraph(stdout,G);

    for(int i=1;i<=5;i++){
    	append(L,i);
    }

    DFS(G,L);
    Graph temp = transpose(G);

    printGraph(stdout,temp);
    printList(L);

    return(0);
}