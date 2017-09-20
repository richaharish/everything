#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
int magicsquare[10][10];

void magicgen(int n)
{
    
   // set all slots as 0
    memset(magicsquare, 0, sizeof(magicsquare));
 
    // Initialize position for 1
    int i = n/2;
    int j = n-1;
 
    // One by one put all values in magic square
    for (int num=1; num <= n*n; )
    {
        if (i==-1 && j==n) //3rd condition
        {
            j = n-2;
            i = 0;
        }
        else
        {
             
            if (j == n)
                j = 0;
             
            if (i < 0)
                i=n-1;
        }
        if (magicsquare[i][j]) //2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicsquare[i][j] = num++; //set number
 
        j++; i--; //1st condition
    }
 
    // Print magic square
    printf("The Magic Square for n=%d:\nSum of each row or column %d:\n\n",
            n, n*(n*n+1)/2);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%3d ", magicsquare[i][j]);
        printf("\n");
    }
}

void check(int no)
{ 
    int flagr=0,flagc=0;
    int temprow,tempcol;
    int diasum1=0,diasum2=0;   
    for(int i=0; i<no ;i++)
    {
        int rowsum=0,colsum=0;
        for(int j=0;j<no;j++)
        {
           rowsum=rowsum + magicsquare[i][j];
           colsum=colsum + magicsquare[j][i];
        }
         printf("The sum of the %d th row ,column:%d ,%d\n",i,rowsum,colsum);
        if(i>0)
        { if((temprow!=rowsum)||(tempcol!=colsum)||(colsum!=rowsum))
           {
              flagr=1;
              break;
           }
         } 
         temprow=rowsum;
         tempcol=colsum;
    }
   if(flagr==0)
   { 
     
       for(int i=0;i<no;i++)
      {
       diasum1=diasum1 + magicsquare[i][i];
       diasum2=diasum2 + magicsquare[i][no-i-1];
      }
    
     printf("The diagonal sums are:%d,%d\n",diasum1,diasum2);
     if(diasum1!=diasum2||diasum1!=tempcol)
    {
          flagc=1;
     }
  }
   if(flagr==0&&flagc==0)
   {
     printf("verified it is a magic square\n");
   }
   else 
     printf("It is not a magic square\n");
}

int main()
{
    int order;
    pid_t pid;

    pid=vfork();
    
    if(pid==0)
   {
     printf("Enter the order of the matrix\n");
     scanf("%d",&order);
     magicgen(order);
   
     exit(0);
   }
   else if(pid>0)
   {
    check(order);
   }

    return 0;
}
 
 
 

 
