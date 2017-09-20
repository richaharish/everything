#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    // create temp arrays  
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[] 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    // Merge the temp arrays back into arr[l..r]
    i = 0; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
     
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
         
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
 
 
void print(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
 
 
 
int main ()
{
  int arr[10];
  pid_t pid;
  pid=vfork();

  if(pid==0)
  { 
    int size;
    printf("Enter the size of the array\n");
    scanf("%d",&size);
    printf("Enter the elements of the array\n");
    for(int i=0;i<size;i++)
    {
      scanf("%d\n",&arr[i]);
    }
    int arr_size = sizeof(arr)/sizeof(arr[0]);
 
    printf("Given array is \n");
    printArray(arr, arr_size);
 
    mergeSort(arr, 0, arr_size - 1);
 
    printf("\nSorted array is \n");
    printArray(arr, arr_size);
   
    exit(0);
  }
  else if(pid>0)
  {


  }
 
}

