//Rishab Jain,pa5,rjain9,12/1/17,cmps101
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){
	FILE *in=NULL;
	FILE *out= NULL;

	// check command line for correct number of arguments
	if( argc != 3 ){
    	printf("Usage: %s <input file> <output file>\n", argv[0]);
    	exit(1);
    }
	
	// open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
    	printf("Unable to open file %s for reading\n", argv[1]);
    	exit(1);
    }
  	if( out==NULL ){
    	printf("Unable to open file %s for writing\n", argv[2]);
    	exit(1);
    }

    int n = 0;
    fscanf(in,"%d", &n);
    Graph temp = newGraph(n);
    int x = 0;
    int y = 0;
    
    while( fgetc(in) != EOF){
    	fscanf(in,"%d %d",&x,&y);

    	if( x!=0 && y!=0){
    		addArc(temp,x,y);
    	}
    	else{
    		break;
    	}
    }


    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out,temp);
    fprintf(out, "\n");

    int listCounter = 1;
    List L = newList();

    while(listCounter != (n+1)){
    	append(L,listCounter);
    	listCounter++;
    }

    DFS(temp,L);
    Graph G = transpose(temp);
    DFS(G,L);

    int c = 0;
    for(int i=1;i<=n;i++){
    	if(getParent(G,i) == NIL){
    		c++;
    	}
    }
    fprintf(out, "G contains %d strongly connected components:\n",c);
    fprintf(out, "Component 1: ");

    List *components = calloc(c+1, sizeof(List));
    
    for(int i=1;i<=c;i++){
    	components[i] = newList();
    }

    moveBack(L);
    int componentCounter = 1;
    while(index(L) != -1){
    	if(getParent(G,get(L)) == NIL){
    		prepend(components[componentCounter],get(L));
    		printList(out,components[componentCounter]);
    		fprintf(out, "\n");
    		if(c != componentCounter){
    			fprintf(out, "Component %d: ",(componentCounter+1));
    			componentCounter++;
    		}
    	}
    	else{
    		prepend(components[componentCounter],get(L));
    	}
      	movePrev(L);
    }

    freeGraph(&temp);
    freeGraph(&G);

    for(int i=1;i<=c;i++){
    	freeList(&components[i]);
    }

    free(&(*components));
    freeList(&L);

    /* close files */
	fclose(in);
	fclose(out);

	return(0);
}