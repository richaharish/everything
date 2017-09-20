#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int adjmat[3][3];
float inv[3][3];

void display(int a[3][3],int n)
{
  printf("display\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
           printf(" %d ",a[i][j]);
        }
         printf("\n");
    }
   printf("\n");
}
void cofactor(int mat[3][3],int tempmat[3][3],int r,int x,int y)
{  
  printf("Inside cofactor %d \n",r);
  int p=0,q=0;
  for(int i=0;i<r;i++)
  {
   
    for(int j=0;j<r;j++)
    {
         if((i!=x) && (j!=y))
         {
           tempmat[p][q]=mat[i][j];
          // printf("temp %d %d %d \n",p,q,tempmat[p][q]); 
           q++;
           if(q==r-1)//very important this is to reset q and increment p
           {
              q=0;
              p++;
           }
         }
         printf("\n");
        
    }
  }
    
   display(tempmat,r-1);

}
int det(int mat1[3][3],int x)
{
   int d=0;
   int sign=1;
   printf("Inside det %d \n",x);
   int temp[3][3];
   if(x==1)
   {
      d=mat1[0][0];
   }
   for(int i=0;i<x;i++)
   {
       printf("passing %d",x);
       cofactor(mat1,temp, x, 0, i);
       d = d + ((sign * mat1[0][i] )* det(temp, x - 1));
       
       sign=-1*sign;
   }
  printf("%d\n",d);
  return(d);
}


void adj(int mat[3][3],int n)
{
  int sign;
  int tempmat[3][3];
  for(int i=0;i<n;i++)
  {
     for(int j=0;j<n;j++)
     {
        
        cofactor(mat,tempmat,n,i,j); //cofactor for each element 

         if((i+j)%2==0)
        {
          sign=1;
        }
         else
        {
          sign=-1;
        }
       printf("hi %d \n",n);
       adjmat[j][i]=(sign)*(det(tempmat,n-1));
       printf("%d , %d =%d\n",j,i,adjmat[j][i]);
     }
  }

   display(adjmat,n);
}


int main ()
{
  pid_t pid;
  int matrix[3][3];
   

  int order;
  
  printf("Enter the order of the square matrix : \n");
  scanf("%d",&order);
//fork call
  pid=vfork();

//child block
  if(pid==0)
  {
    printf("Enter the elements of the matrix\n");   //matrix values
    for(int i=0;i<order;i++)
    {
        for(int j=0;j<order;j++)
        {
          printf("Enter the %d,%d th element:",i,j);
          scanf("%d",&matrix[i][j]);
        }
        printf("\n");
    }
    
    display(matrix,order);
 
    exit(0);
  }
  else if(pid>0)
  {
    
    adj(matrix , order);
    

    float d=det(matrix,order);
    printf("determinant %f\n\n",d);
    if(d==0)
    {
      printf("The matrix is not invertible as det = 0\n");
    }
    else
    {
       display(adjmat,order);
       printf("\n\n-----------ans-------------\n");
       for(int i=0;i<order;i++)
       {
         for(int j=0;j<order;j++)
         {
            inv[i][j] = adjmat[i][j]/d; 
            printf(" %f ",inv[i][j]);
         }
         printf("\n");
       }
    }
     
     //display(inv,order);
  }
}
