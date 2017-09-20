#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
   int size;
   int array[10];
   
   printf("Enter the  size of the array:\n");
   scanf("%d",&size);
   printf("Enter the elements of the array:\n");
   
   for(int i=0;i<size;i++)
   {
      scanf("%d",&array[i]);
      
   }
    
   //display
   for(int i=0;i<size;i++)
   {
      printf("%d\t",array[i]);
   }
   printf("\n");
   
   int pid= fork();
   
  if(pid==0)
  {
    //ascending sort bubble 
    
    for(int i=0;i<size-1;i++)
    {
      for(int j=0;j<size-i-1;j++)
      {
         if(array[j]>array[j+1])
         {
           int temp = array[j];
           array[j]=array[j+1];
           array[j+1]=temp;
         }
      }
    }
     printf("The ascending order sorted array:\n");
     for(int i=0;i<size;i++)
     {
        printf("%d\t",array[i]);
     }
     printf("\n");
  }

  else
  {
     //descending sort bubble 
    
    for(int i=0;i<size-1;i++)
    {
      for(int j=0;j<size-i-1;j++)
      {
         if(array[j]<array[j+1])
         {
           int temp = array[j];
           array[j]=array[j+1];
           array[j+1]=temp;
         }
      }
    }
     printf("The  descending order sorted array:\n");
     for(int i=0;i<size;i++)
     {
        printf("%d\t",array[i]);
     }
     printf("\n");
  }

   return(0);
}
