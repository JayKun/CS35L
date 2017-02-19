#include <stdlib.h>
#include <stdio.h>

char decrypt(const char a){
  return a^42; 
}
 
int frobcmp(char const* a, char const* b){

  while(*a!=' ' && *b!=' '){
    if(decrypt(*a) > decrypt(*b))
      return 1;
    else if (decrypt(*b)>decrypt(*a))
      return -1; 
    a++;
    b++;
  }
  
  if(*a!=' ' && *b==' ')
    return 1; 
  else if ( *a==' ' && *b!=' ')
    return -1; 
  else if ( *a==*b)
    return 0; 
  else
    printf("Something is wrong"); 
}

int compare(const void* a, const void* b)
{
  return frobcmp(*((const char **)a), *((const char **)b));
}

void writeOut(const char* c)
{
  while(1)
    {
      putchar(*c);
      if (*c== ' ')
	return;
      c++;
    }
}


int main(){

  size_t bufferSize=10, numChars=0, numWords=0; 
  char *buffPtr = (char*)malloc(sizeof(char)*bufferSize); 
  char *tempPtr = buffPtr;
  char **words;
  char next=getchar();
  int isEOF=feof(stdin);
  while(!isEOF)
    {
      int isSpace=0; 
      char c=next;
      //check error;      
      numChars++;

      if(numChars==bufferSize-1){
	bufferSize*=2; 
	tempPtr=(char*)realloc(tempPtr, sizeof(char)*bufferSize);
	buffPtr=&(tempPtr[numChars-1]);
      }
      
      *buffPtr=c;
      buffPtr++;
 
      if(c==' '){
	numWords++;
	isSpace=1; 
      }
      
      next=getchar();
      isEOF=feof(stdin);
      if(isEOF && isSpace==0){
	*buffPtr=' ';
	numChars++; 
	numWords++; 
      }
    }
 

  words=(char**)malloc(sizeof(char*)*(numWords+1));
  int j;
  int wordCounter=0;
  char* ptr=tempPtr;
  char* startPtr = tempPtr; 
  for(j=0;j<numChars;j++){
    char b=*ptr; 
    if(b==' ')
      {
	words[wordCounter]=startPtr;
	wordCounter++; 
	startPtr=ptr+1;
      }
    if(j==numChars-1)
      words[wordCounter]=startPtr; 
    ptr++;
  } 

  qsort(words, numWords, sizeof(char*), compare);
  
  /*  
  int i; 
  char *a=tempPtr;
  
  for(i=0; i<numChars; i++)
    {
      
      printf("%c", *a);	  
      a++;
     }
      
  */  
  
  size_t i;
  for (i = 0; i < numWords; i++)
     writeOut(words[i]);
  free(words);
  free(tempPtr);
}
