#include<iostream>
#include"schedule.h"
using namespace std;

int main ()
{   
    schedule s;
    int choice,index;
    char stop = 'n';
    while(stop =='n')
    {
      cout<<"Enter 1.for fcfs  2.for sjf  3.for srt  4.priority non preemptive 5. priority preemptive  6.hrrn 7.round robin 8.print the table "<<endl;
      cin>>choice;
 
        switch(choice) 
       {
           case 1:
              s.input();
              index = s.fcfs();
              break;
           case 2:
              index = s.sjf();
              break;
           case 3:
              index = s.srt();
              break;
           case 4:
              index = s.priority();
              break;
           case 5:
              index = s.priorityp();
              break;
           case 6:
              index = s.hrrn();
              break;
           case 7:
              index = s.roundrobin();
              break;
           case 8:
              s.print(index);
              break;
           default:
              cout<<"Invalid choice please re-enter"<<endl;
              break;    
       }  
      
      cout<<"Do you want to stop y/n"<<endl;
      cin>>stop;

   }
   return (0);
}
