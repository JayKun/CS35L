#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
  // (a) Check for number of arguments
  if(argc!=3){
    fprintf(stderr, "Incorrect number of arguments.\n");
    exit(1); 
  }
  // (b) Check for equal length
  char* from=argv[1];
  char* to=argv[2];
  
  if(strlen(from)!=strlen(to)){
    fprintf(stderr, "Arguments must be of the same length.\n");
    exit(1); 
  }
  // (c) Check for duplicates
  size_t i, j; 
  for(i=0;i<strlen(from);i++)
    for(j=i+1;j<strlen(from);j++){
      if(from[i]==from[j]){
	fprintf(stderr, "First Argument contain duplicates.\n");
	exit(1); 
      }
    }

  //(d)Traliterate files
  char c=getchar();
  size_t numChars=0;
  int length=strlen(from);
  int isEOL=feof(stdin);
 
  while(!isEOL){
    numChars++; 
    int isTred=0;
    for(i=0;i<length;i++)
      if(c==from[i]){
	putchar(to[i]); 
	isTred=1; 
      }
    if(!isTred)
      putchar(c);
    c=getchar();
    isEOL=feof(stdin);
  }
  
  
}
