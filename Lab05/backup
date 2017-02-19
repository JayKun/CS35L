#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int ignoreCase=0;

char decrypt(const char a){
  if(ignoreCase){
    char c= a^42; 
    return (toupper((unsigned char)c));
  }
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
      ssize_t res = write(1, c, 1);
      if(ferror(stdout))
	{
	  fprintf(stderr, "Output Error");
	  exit(1);
	}
      if(res<0)
	{
	  fprintf(stderr, "Output Error.\n");
	  exit(1);
	}
      if (*c== ' ')
	return;
      c++;
    }
}

int detectInErr()
{
  if(ferror(stdin))
    {
      fprintf(stderr, "Error reading file.\n");
      exit(-1);
    }
}

void detectMemErr(const void *ptr)
{
  if(ptr==NULL)
    {
      fprintf(stderr, "Failed to allocate memory.");
      exit(-1);
    }
}

int main(int argc, char* argv[]){
  struct stat fileStat;
  ssize_t res = fstat(STDIN_FILENO, &fileStat);
  if(res < 0){
      fprintf(stderr, "Error with fstat!");
      exit(1);
   }
  size_t fileSize=fileStat.st_size+2;
  size_t bufferSize=fileSize, numChars=0, numWords=0; 
  char *buffPtr = (char*)malloc(sizeof(char)*bufferSize); 
  detectMemErr(buffPtr);
  char *tempPtr = buffPtr;
  char **words; 
  
   if(argc>2){
    fprintf(stderr, "Incorrect number of arguments.\n");
    exit(1);
   }
  if(argc==2){
    if(!strcmp(argv[1],"-f"))
      ignoreCase=1;
    else
      {
	fprintf(stderr, "Incorrect Option.\n");
	exit(1);
      }
  }
  



  char next[2];
  size_t bytesRead=read(0, &next, 1);
  //  printf("Char is %c with %d bytes read.\n", next[0], bytesRead);
  if(bytesRead<0)
    {
      fprintf(stderr, "Error reading.\n");
      exit(1);
    }
  detectInErr();
  // int isEOF=feof(stdin);
  while(bytesRead==1)
    {
      
      int isSpace=0;
      
      //char* c= next[0];
      //printf("%c", next[0]);
      //check error;      
      numChars++;
       if(numChars==bufferSize-1){
	bufferSize*=2; 
	tempPtr=(char*)realloc(tempPtr, sizeof(char)*bufferSize);
	detectMemErr(tempPtr); 
	buffPtr=&(tempPtr[numChars-1]);
      }
      
      *buffPtr=*next;
      buffPtr++;
      if(*next==' '){
	numWords++;
	isSpace=1; 
      }

      bytesRead=read(0, &next, 1);
      detectInErr(); 
      //isEOF=feof(stdin);
      if(bytesRead!=1 && isSpace==0){
	*buffPtr=' ';
	numChars++; 
	numWords++; 
      }
   }
 

  words=(char**)malloc(sizeof(char*)*(numWords+1));
  detectMemErr(words);
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
  
   
  size_t i;
  for (i = 0; i < numWords; i++)
     writeOut(words[i]);
  free(words);
  free(tempPtr);
}
