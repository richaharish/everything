#include"schedule.h"
#include<iostream>
using namespace std;
//non-preemptive

  int schedule::fcfs()
  {
     //entering inputs

      

     /*char stop='n' ;
     int i=0;
     
     while(stop=='n')
     {
        cout<<"Enter the process id ,arrival time and burst time "<<endl;
        cin>>pid[i];
        cin>>arrivaltime[i];
     	cin>>bursttime[i];
        cout<<"Is this the last process y/n"<<endl;
        cin>>stop;

        i++;
     }*/
     
     int i=n;
   
     int check[i]={0};
          
     //to find the minimum
     int index;
     for(int k=0;k<i;k++)
    {
        int minimum=100;
        for(int j=0;j<i;j++)
       {
          if((check[j]==0)&&(arrivaltime[j]<minimum))
          {
             minimum=arrivaltime[j];
             index=j;
          }
       }
        int CT;
        check[index]=1;
        if(k==0)                                           //calculation of CT for first time
        {
           completiontime[index]=arrivaltime[index]+bursttime[index];
              
        }
        else                                                //calculation of CT
        {
           if(arrivaltime[index]<=CT)
           completiontime[index]=CT+bursttime[index];
            else
         completiontime[index]=arrivaltime[index]+bursttime[index];
        }
        TAT[index]=completiontime[index]-arrivaltime[index]; //calculation of TAT
        waittime[index]=TAT[index]-bursttime[index];       //calculation of WT
        CT=completiontime[index];                        //storing the completion tme 
           
    } 
              
       int avg_waittime=0;
       for(int j=0;j<i;j++)
       { 
           
          avg_waittime=avg_waittime+waittime[j]; 
          
       } 

       avg_waittime=avg_waittime/i;

       cout<<"The average wait time is "<<avg_waittime<<endl;

  return(i);
}














