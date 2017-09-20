#include"schedule.h"
#include<iostream>
using namespace std;

 
 
   void schedule::read()
   {
     char stop=n ;
     cout<<"Enter the process id ,arrival time and burst time "<<endln;
    
     
     public int i=0;
     while(stop==n)
     {
        cin>>pid[i];
        cin>>arrivaltime[i];
     	cin>>bursttime[i];
        cout<<"Is this the last process y/n"<<endln;
        cin>>stop;

        i++;
     }
 
   }
