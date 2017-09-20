#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
   int n;
   printf("Enter the last no");
   scanf("%d",&n);
   
   if(fork()==0)
   {
     printf("The odd series is:\n");
     for(int i=1;i<=n;i++)
     {
        if(i%2!= 0)
        {
          printf(" %d ",i);
         }
     }
     printf("\n");
   }
   else if(fork()>0)
   {  
      printf("The even series is :\n");
      for(int i=1;i<=n;i++)
     {
        if(i%2 == 0)
        {
          printf(" %d ",i);
         }
     }
     printf("\n");
   }

}
