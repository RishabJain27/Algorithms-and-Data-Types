//Rishab Jain,pa4,rjain9,11/18/17,cmps101
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
	Graph A = newGraph(30);

    addArc(A,1,2);
    addArc(A,2,4);
    addArc(A,2,5);
    addArc(A,2,6);
    addArc(A,3,4);
    addArc(A,4,5);
    addArc(A,5,6);

    printGraph(stdout,A);
}