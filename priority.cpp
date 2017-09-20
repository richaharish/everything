#include<iostream>
#include"schedule.h"

//priority non preemptive 

using namespace std;

int schedule::priority()
{
     int index,index1;
     char stop='n' ;
     int i=0;
     
     while(stop == 'n')
     {
        cout<<"Enter the process id ,arrival time ,burst time and priority "<<endl;
        cin>>pid[i];
        cin>>arrivaltime[i];
     	cin>>bursttime[i];
        cin>>pri[i];

        cout<<"Is this the last process y/n"<<endl;
        cin>>stop;

        i++;
     }
     
     int checker[i]={0};
     //sorting the data
     for(int k=0;k<i-1;k++)
     {
        for(int j=0;j<i-1-k;j++)
        {
            if(arrivaltime[j]>arrivaltime[j+1])
            {
               //for arrival time
               int temp= arrivaltime[j];
               arrivaltime[j]=arrivaltime[j+1];
               arrivaltime[j+1]=temp;
               
               //for burst time
               temp=bursttime[j];
               bursttime[j]=bursttime[j+1];
               bursttime[j+1]=temp;
           
               //for pid
               temp=pid[j];
               pid[j]=pid[j+1];
               pid[j+1]=temp;

               //for priority
               temp=pri[j];
               pri[j]=pri[j+1];
               pri[j+1]=temp;
            }
        }

    }
 

   for(int k=0;k<i;k++)
   {
     int min=100,max=0;
        for(int j=0;j<i;j++)
       {
           if((k==0)&&(checker[j]==0)&&(arrivaltime[j]<min))
           {
               min=arrivaltime[j];
                index1=j;
           }
           else if ((k!=0)&&(checker[j]==0)&&(pri[j]>max))
           {
                max=pri[j];
                index1=j;
           }
       } 

        cout<<"max"<<max<<endl;
        cout<<"index"<<index1<<endl;

        checker[index1]=1;
        int CT;
       if(k==0)
       {
          completiontime[index1]=arrivaltime[index1]+bursttime[index1];
          
         }
       else 
       {
          completiontime[index1]=CT+bursttime[index1];
       }

       TAT[index1]=completiontime[index1]-arrivaltime[index1];
       waittime[index1]=TAT[index1]-bursttime[index1]; 
       CT=completiontime[index1];

     
   }

 return(i);
}
