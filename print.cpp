#include"schedule.h"
#include<iostream>
using namespace std;

void schedule::print(int row)
{
    cout<<"The table is as follows"<<endl;
    cout<<"Pid   AT   BT     CT    TAT    WT"<<endl;
    
    for(int i=0;i<row;i++)
    {
       cout<<pid[i]<<"    "<<arrivaltime[i]<<"     "<<bursttime[i]<<"     "<<completiontime[i]<<"     "<<TAT[i]<<"     "<<waittime[i]<<endl;
    }
    
     
}
