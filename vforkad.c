#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

void asc(int x,int arr[])
{
   //ascending sort bubble 
    
   int temp;

    for(int i=0;i<x/2-1;i++)
    {
      for(int j=0;j<x/2-i-1;j++)
      {
         if(arr[j]>arr[j+1])
         {
           int temp = arr[j];
           arr[j]=arr[j+1];
           arr[j+1]=temp;
         }
      }
    }
     printf("The ascending order sorted array:\n");
     for(int i=0;i<x/2;i++)
     {
        printf("%d\t",arr[i]);
     }
     printf("\n");
}
void desc(int x,int arr[])
{
   //descending sort bubble 
    
    for(int i=x/2;i<x-1;i++)
    {
      for(int j=x/2;j<x-i-1;j++)
      {
         if(arr[j]<arr[j+1])
         {
           int temp = arr[j];
           arr[j]=arr[j+1];
           arr[j+1]=temp;
         }
      }
    }
     printf("The  descending order sorted array:\n");
     for(int i=x/2;i<x;i++)
     {
        printf("%d\t",arr[i]);
     }
     printf("\n");
  }
int main()
{
  int size,n,array[10];
  int pid=vfork();
   

  if(pid==0)
 { 
   //storing values into the file //child wil run first in vfork();
    
   printf("Enter the size of the array:\n");
   scanf("%d",&size);
   printf("Enter the values:\n");
   for(int i=0;i<size;i++)
   {
      scanf("%d",&array[i]);
      
   }
    
   desc(size,array);
   exit(0);  //should be present in parent when we use vfork() otherwise it goes to infiniteloop
 }

else
 {
   asc(size,array);
 }
  return(0);
}
