//Rishab Jain,pa4,rjain9,11/18/17
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
    		addEdge(temp,x,y);
    	}
    	else{
    		break;
    	}
    }

    printGraph(out,temp);
    fprintf(out, "\n");
    int i =0;
    int z = 0;

    while(fgetc(in) != EOF){
    	fscanf(in,"%d %d",&i,&z);
    	if(i==0 && z==0){
    		break;
    	}
    	
    	BFS(temp,i);
    	List temp2 = newList();
    	getPath(temp2,temp,z);

    	if(getDist(temp,z)== INF){
    		fprintf(out,"The distance from %d to %d is infinity\n",i,z);
    		fprintf(out, "No %d-%d path exists \n\n",i,z);
    		freeList(&temp2);
    	}
    	else{
    		fprintf(out, "The distance from %d to %d is %d\n",i,z,getDist(temp,z));
    		fprintf(out, "A shortest %d-%d path is: ",i,z);
    		printList(out,temp2);
    		fprintf(out, "\n\n");
    		freeList(&temp2);
    	}
    }

    
    freeGraph(&temp);

    /* close files */
	fclose(in);
	fclose(out);

	return(0);

}