#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
   int n,no,c,choice;
   int pid=vfork();
   if(pid>0)
   {     

       printf("Enter the no :\n");
       scanf("%d",&n);
       
        
   }
   else 
   {
       sleep(50);
       //printf("Enter 1.fibonacci 2.prime \n");
       //scanf("%d",&choice);
       //switch(choice)
       //{
        //case 1:
             {  int a=0,b=1;
                for(int k=0;k<n;k++)
                {
	          if(k==0||k==1)
                  {
                   printf("%d\n",k);
                  }
	         else
	        {
	           c = a+b;
	           printf("%d\n",c);
	           a=b;
	           b=c;
	        }

	        }
           //    break;
            }
      // case 2:
            { int i,j;
              printf("The prime numbers between 1 and %d are :\n",n);
              for(i=2;i<n;i++)
              {
                 int flag=0;
                 for(j=2;j<i;j++)
              {   
                 float num=i%j;
          
                 if(num==0.0)
                {
                  flag=1;
                  break;
                 }   
              }
       
              if(flag==0)
             {
                printf("%d\n",i);
             }
             }
            // break;
           }
      //default:
            exit(0);
        //    break;
      
       

     }
   return(0);
}
   
 
 
