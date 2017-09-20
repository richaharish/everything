#include<iostream>
#include"schedule.h"

using namespace std;

int schedule::roundrobin()
{  
    int rem, temp;
   //entering inputs
     char stop='n' ;
     int i=0;
  
     front=-1;
     rear=-1;
  
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
               if(bursttime[j]>bursttime[j+1])
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
  
    
    

       //remaining time
      for(int j=0;j<i;j++)
      {
         remainingtime[j]=bursttime[j];
         cout<<"remai"<<remainingtime[j]<<endl;
      }

     //setting value of time quantum
      cout<<"enter the value for time quantum :";
      cin>>timequantum;
     
     
      int index;
      int time=arrivaltime[0];
      int checker=0;
        while(checker!=i)
       {     

             cout<<"time"<<time<<endl;
            //number of process arriving at a particular instant
             if((time==arrivaltime[i-1])||(time>arrivaltime[i-1]))
             {
                 index=i; 
             }
             else
             {
	         for(int j=0;j<i;j++)
	         {
	              if(arrivaltime[j]>time)
	             {
                         index=j;
	                 break;
                     }
	         }
             }
            
             cout<<"index"<<index<<endl;
             
             //
             for(int j=0;j<index;j++)
             {
                  if(check[j]==0)
                    { 
                       cout<<"entering into the rq"<<j<<endl;
                       enqueue(j);
                       check[j]=1;
                    } 
             }
              cout<<"check array"<<endl;

              for(int j=0;j<i;j++)
             {
                 
                 cout<<check[j]<<endl;
             }


              if(time!=arrivaltime[0]&&(check[rem]!=2))
             {
                
                enqueue(rem);

             }
 
              rem=dequeue();
              cout<<"rem"<<rem<<endl;
              //
              if(remainingtime[rem]<=timequantum)
              {
                 cout<<"hi end"<<endl;
                 time=time+remainingtime[rem];
                 cout<<"time"<<time<<endl;
                 remainingtime[rem]=0;
                 checker++;
                 check[rem]=2;
                 
                 completiontime[rem]=time;
                 TAT[rem]=completiontime[rem]-arrivaltime[rem];
                 waittime[rem]=TAT[rem]-bursttime[rem];
              }
              else
              {
                 cout<<"hello"<<endl;
                 remainingtime[rem]=remainingtime[rem]-timequantum;
                 time=time+timequantum;
              }
        }
       return(i);
 }
