#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
  
  int pid,pid1;
 
  //exercise 1:
  /*
  fork();
  printf("hi\n ");
  fork();
  printf("bye\n ");
  fork();
  printf("hello\n ");
  */
  
  //exercise 2:
  
  /*
  pid =fork();

  printf("%d\n",pid);

  if(pid < 0)
  {
     fprintf(stderr,"failed fork \n");
  }
  else if(pid == 0)
  {
    pid1=fork();
     printf("%d\n",pid1);
     printf("child \n");
  }
  else if(pid>0)
  {
     printf(" parent\n ");
  }

  printf("hello\n");*/

 //exercise 3:                      //1=2;2=10;hello=20;

  fork();
  printf("1\n");
  fork() && fork() ||fork() ;
  printf("2\n");
  fork();
  printf("hello\n");
  printf("r");  

return 0;
}   
