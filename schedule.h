
class schedule

{
   //data declaration 
   private :
     char pid[10];
     int arrivaltime[10],bursttime[10],completiontime[10],TAT[10],waittime[10],remainingtime[10],n,pri[10];
     int timequantum ,readyq[20] , front,rear ;

   //method declaration 
   public:
     void print(int i);
     int fcfs();
     int sjf();
     int srt();
     void input();
     int priority();
     int priorityp();
     int hrrn();
     int roundrobin();
     void enqueue(int);
     int dequeue();

};
