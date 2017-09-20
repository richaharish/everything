#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
 
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
 
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];  
    printf("pivot %d\n",pivot);  
    int i = (low - 1);   
 
    for (int j = low; j <= high - 1; j++)
    {
         
        if (arr[j] <= pivot)
        {
            i++;     
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    
    return (i+1);
}
 
 
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
         
        int pi = partition(arr, low, high);
 
         
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
 
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
       {
          printf("%d ", arr[i]);
       }
    printf("\n");
}
 
 
int main()
{
    int size;
    int pi;
    

    printf("Enter the size of the array\n");
    scanf("%d",&size);
   
    int arr[size];

    printf("Enter the elements of the array\n");
    for(int i=0;i<size;i++)
    {
      scanf("%d\n",&arr[i]);
    }

    printArray(arr, size);

    pid_t pid;

    int low=0,high=size-1;

    pid=vfork();
    if(pid==0)
    {
      pi = partition(arr, low, high);
      exit(1);
    }
    else if(pid>0)
    {
       
       quickSort(arr, low, pi - 1);
       quickSort(arr, pi + 1, high);
    }
    
    printf("Sorted array: ");
    printArray(arr, size);
    return 0;
}

