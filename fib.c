#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
   int n,c,choice;
   int pid=vfork();
   if(pid>0)
   {     
       int a=0,b=1;
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
      
       
        
   }
   else 
   { 
        
         printf("Enter the no :\n");
       scanf("%d",&n);
       exit(0);
        
  }
return(0);
}
