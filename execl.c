#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{ 

  pid_t pid=fork();

  if(pid<0)
  {
      printf("Fork failed\n");
  }
  else if(pid==0)
  {
    printf("Welcome into child\n");
    execl("/bin/ls","ls","-lt",NULL);
    exit(0);
   }
  else if(pid>0)
   {
     printf("Welcome to the parent\n ");
   }
   return(0);
}
