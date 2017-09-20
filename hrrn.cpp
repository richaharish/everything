#include"schedule.h"
#include<iostream>

using namespace std;

//hrrn non-preemptive

int schedule::hrrn()
{
    
     //entering inputs
     char stop='n' ;
     int i=0;
     int CT;
     float RR;
     while(stop=='n')
     {
        cout<<"Enter the process id ,arrival time and burst time "<<endl;
        cin>>pid[i];
        cin>>arrivaltime[i];
     	cin>>bursttime[i];
        cout<<"Is this the last process y/n"<<endl;
        cin>>stop;

        i++;
     }
    
   
     int check[i]={0};
     int temp;     
      //sorting the data
     for(int k=0;k<i-1;k++)
     {
        for(int j=0;j<i-1-k;j++)
        {
            if(arrivaltime[j]>arrivaltime[j+1])
            {
               //for arrival time
               temp= arrivaltime[j];
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
                
            }
            else if(arrivaltime[j]==arrivaltime[j+1])
           {
               if(pid[j]>pid[j+1])
                {
                    temp=bursttime[j];
                    bursttime[j]=bursttime[j+1];
                    bursttime[j+1]=temp;

                    temp= arrivaltime[j];
                    arrivaltime[j]=arrivaltime[j+1];
                    arrivaltime[j+1]=temp;

                    temp=pid[j];
                    pid[j]=pid[j+1];
                    pid[j+1]=temp;

                }
           }
        }
     }
     int index;
     float wait,max;
     
     cout<<"check"<<endl;
     for(int j=0;j<i;j++)
     {
         cout<<check[j]<<endl; 
     }
     for(int k=0;k<i;k++)
     {
        max=0;
        if((k==0)&&(check[k]==0))
        {
            index=0;
            completiontime[index]=arrivaltime[index]+bursttime[index];
            
        }
        else if((k>0))
        {
             for(int j=0;j<i;j++)
             {
                  if((check[j]==0)&&(arrivaltime[j]<=CT))
                  {
                     wait=CT-arrivaltime[j];
                     RR=(wait+bursttime[j])/bursttime[j];
                     if(RR>max)
                     {
                        max=RR;
                        index=j;
                     }
                 } 
             }
            
             completiontime[index]=CT+bursttime[index];

        }
       cout<<"index"<<index<<endl; 
       CT=completiontime[index];
       check[index]=1;
       TAT[index]=completiontime[index]-arrivaltime[index];
       waittime[index]=TAT[index]-bursttime[index];
 
     }
   return (i);
}
