#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main ()
{
  if(fork()==0)
  {
    printf("Welcome to child block\n");
    sleep(1);
    printf("I am an orphan\n");
  }
  else
  {
    printf("Welcome into the parent block\n");  
    exit(0);
  }
}
