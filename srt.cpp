#include"schedule.h"
#include<iostream>

using namespace std;

//SRT preemptive

int schedule::srt()
{
     
     int check=0,index;
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
         
       cout<<"time"<<time<<endl;
        cout<<"at"<<arrivaltime[i-1]<<endl;

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
        int min=1000,index2 ,index1 ,min1;
        int flag=0,flag1=0;

       // to find the minimum

        for(int k=0;k<index;k++)
        { 
            flag=1;
            if((remainingtime[k]<min) && (checker[k]==0))
            {
               min=remainingtime[k];
               index2=k;
            }
        } 
        cout<<remainingtime[index2]<<endl;
             
        min1 = arrivaltime[index2];
        cout<<"min"<<min1<<endl;
        cout<<"flag"<<flag<<endl;
        if(flag==1)
        {  
            for(int k=0;k<index;k++)
            {
                   cout<<"hi"<<endl;
		   if(bursttime[k]==bursttime[index2])
		    {
		       
		       if((arrivaltime[k]<min1)&&(checker[k]==0))
		       {
                           flag1=1;
		           min1=arrivaltime[k];
                           cout<<"k"<<k<<endl;
		           index1=k;
                           cout<<"index"<<index1<<endl;
		       }
		    }
                   
             }
       }
       cout<<"flag1"<<flag1<<endl;
       cout<<"final min"<<min1<<endl;
       //cout<<"index"<<index1<<endl;

       if(flag1==1)
	{      remainingtime[index1]=remainingtime[index1]-1;
	       if(remainingtime[index1]==0)
	       {    checker[index1]=1;
		    completiontime[index1]=time+1;
		    TAT[index1]=completiontime[index1]-arrivaltime[index1];   //calculation
		    waittime[index1]=TAT[index1]-bursttime[index1];
	       }
        }
       else
       {
          remainingtime[index2]=remainingtime[index2]-1;
	       if(remainingtime[index2]==0)
	       {
                    checker[index2]=1;
		    completiontime[index2]=time+1;
		    TAT[index2]=completiontime[index2]-arrivaltime[index2];   //calculation
		    waittime[index2]=TAT[index2]-bursttime[index2];
	       }
       }
        cout<<"remaining time"<<endl;
        int sum=0;
        for(int j=0;j<i;j++)
       { 
          cout<<remainingtime[j]<<endl;
          sum=sum+remainingtime[j]; 
          
       } 

        cout<<"checker"<<endl;
        for(int j=0;j<i;j++)
        {
          cout<<checker[j]<<endl;
        }
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

