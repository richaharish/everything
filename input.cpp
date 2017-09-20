#include"schedule.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include<sstream>
#include<time.h>
#include<sys/stat.h>
#include<cstdlib>

using namespace std;

void  schedule::input()
{
    n=5;

   fstream file;
   for(int j=0;j<n;j++)
   {
      pid[j]=j;
      

      file.open("burstinput.txt");
      char string1[100],string2[100],string3[100];
      
      cout<<"Enter the file name ";
      cin>>string3;
      strcpy(string1," wc -w ");
      strcat(string1,string3);
      strcpy(string2,"| cut -f1 -d '' > burstinput.txt");
      strcat(string1,string2);
      system(string1);
      file>>bursttime[j];
      file.close();


     struct stat t_stat;
     stat(string3,&t_stat);
   
     struct tm *timeinfo = localtime(&t_stat.st_ctime);

     //int hours=timeinfo->tm_hour;
     
     //int minutes=timeinfo->tm_min; 
     int seconds=timeinfo->tm_sec;

   //  cout<<hours<<"  "<<minutes<<"  "<<seconds<<"   "<<endl;

     arrivaltime[j] =  seconds;

     
   }
}
