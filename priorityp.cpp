#include"schedule.h"
#include<iostream>

using namespace std;

//priority preemptive

int schedule::priorityp()
{
     
     int index;
     int sum=0;
     //entering inputs
     char stop='n' ;
     int i=0;
     
     while(stop == 'n')
     {
        cout<<"Enter the process id ,arrival time and burst time "<<endl;
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
      //remainingtime[i-k-1]=bursttime[i-k-1];
        
     }
     //remaining time
      for(int j=0;j<i;j++)
      {
         remainingtime[j]=bursttime[j];

      }

   int time=0;
    
  
    int add=1;
    while(add!=0)
     { 
         
        
        //checking if there are any arrival at that time 
        if((time==arrivaltime[i-1])||(time>arrivaltime[i-1]))
        {
              index=i;
        }
        else
        {
             for(int j=0;j<i;j++)
	     {
		   
	        if(time<arrivaltime[j])
		{  
                   if(time==0)
                   {
                    time++;
                    continue;
                   }
		   index=j;
		   cout<<index<<endl;
		   break;
		}        
             }
        }
        int max=0, index1;

      // to find the max priority
        for(int k=0; k<index;k++)
        {
           if((pri[k]>max)&&(checker[k]==0))
           {
               max=pri[k];
               index1=k;

           }
        }
        
        remainingtime[index1]=remainingtime[index1]-1;
        if(remainingtime[index1]==0)
        {
           checker[index1]=1;
           completiontime[index1]=time+1;
           TAT[index1]=completiontime[index1]-arrivaltime[index1];
           waittime[index1]=TAT[index1]-bursttime[index1];
        }
      
        //cout<<"remaining time"<<endl;
        int sum=0;
        for(int j=0;j<i;j++)
       { 
          //cout<<remainingtime[j]<<endl;
          sum=sum+remainingtime[j]; 
          
       } 

       /* cout<<"checker"<<endl;
        for(int j=0;j<i;j++)
        {
          cout<<checker[j]<<endl;
        }*/
       add=sum;
       time++;
            
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

