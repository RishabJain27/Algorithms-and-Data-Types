//Rishab Jain,rjain9, pa2, cmps101
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#define MAX_LEN 160

int main(int argc, char * argv[]){

int i=0;
int  count=0;
FILE *in=NULL;
FILE *out= NULL;
char line[MAX_LEN];
//char tokenlist[MAX_LEN];
//char* token;

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


  /* read each line of input file, then count and print tokens */
  while( fgets(line, MAX_LEN, in) != NULL)  {
    count++;
  }  
  fclose(in);
  in = fopen(argv[1], "r");

  char *lineArray[count];
  
  while(fgets(line,MAX_LEN,in) != NULL){
    lineArray[i] = malloc(strlen(line)+1);
    strcpy(lineArray[i],line);
    i++;
  }

  List B = newList();
  append(B,0);
  moveFront(B);

  for(i=1;i<count;i++){
   	char * temp = lineArray[i];
    moveFront(B);
    while(index(B) >= 0 && strcmp(temp,lineArray[get(B)]) >0){
      moveNext(B);
    }
    
    if(index(B) < 0){
      append(B,i);
    }
    else{
      insertBefore(B,i);
    }
  }

  moveFront(B);
  while(index(B) >= 0){
    fprintf(out, lineArray[get(B)]);
    moveNext(B);
  }


  for(i=0; i<count;i++){
  	free(lineArray[i]);
  }

  clear(B);
  freeList(&B);

  /* close files */
  fclose(in);
  fclose(out);

  return(0);
}
