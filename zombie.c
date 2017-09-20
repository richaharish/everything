#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

//zombie process
int main()
{
   if(fork()>0)
   {
      printf("Inside parent block\n");
      sleep(5);
      printf("child is dead\n");
   }
   else 
   {
     printf("Inside the child block\n");
     exit(0);
      
   }
   return(0);
}

