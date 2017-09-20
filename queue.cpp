#include<iostream>
#include"schedule.h"

using namespace std;

void schedule::enqueue(int value)
{
  if(front==-1)
     front=0;
  rear=rear+1;
  readyq[rear]=value;

}

int schedule::dequeue()
{
  int value = readyq[front];
  front=front+1;
  return(value);
}
