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
     //printf("The ascending order sorted array:\n");
     for(int i=0;i<=x/2;i++)
     {
        printf("%d\t",arr[i]);
     }
     printf("\n");
}
void desc(int x,int arr[])
{
   //descending sort bubble 
    
    for(int i=x/2+1;i<x-1;i++)
    {
      for(int j=x/2+1;j<x-i-1;j++)
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
     for(int i=x/2+1;i<x;i++)
     {
        printf("%d\t",arr[i]);
     }
     printf("\n");
  }



int main()
{
  int size,n,array[10];
  int pid=fork();
  FILE *fp;

  if(pid==0)
 { 
   sleep(50);
   fp=fopen("store.txt","r");
   fscanf(fp,"%d",&n);
   int a[n];
   for(int k=0;k<n;k++)
   {
      fscanf(fp,"%d",&a[k]);
   }
    desc(n,a);
    fclose(fp);
   fclose(fp);  
 }
 else
 {
  //storing values into the file 
   fp=fopen("store.txt","w");
   printf("Enter the size of the array:\n");
   scanf("%d",&size);
   fprintf(fp,"%d\n\n",size);
	   fclose(fp);
   fp=fopen("store.txt","a");
   printf("Enter the values:\n");
   for(int i=0;i<size;i++)
   {
      scanf("%d",&array[i]);
      fprintf(fp,"%d\n",array[i]);
   }
   fclose(fp);
   
  
   fp=fopen("store.txt","r");
   fscanf(fp,"%d",&n);
    
   int a[n];
   for(int k=0;k<n;k++)
   {
      fscanf(fp,"%d",&a[k]);
   }
    asc(n,a);
    fclose(fp);
 }
}
