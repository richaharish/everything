#include "scheduler.h"
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<sstream>
#include<sys/stat.h>
#include<time.h>
#include<iostream>
using namespace std;

void scheduler::files()
{
	cout<<"Enter the number of processes"<<endl;
	cin>>n;
	//n=5;
	fstream file; // Stream class to both read and write from/to files.
	int i;
	for(i=1;i<=n;i++)
	{
		pid[i]=i;
		
		file.open("file.txt");
		char s[50],s1[50],s2[50];
		cout<<"Enter the file name"<<endl;
		cin>>s2;
		
		// wc -w file_1.txt outputs 4 file_1.txt
		// wc -w file_1.txt| cut -f1 -d ' ' outputs 4
		
		strcpy(s,"wc -w "); // Gives the number of words and the filename
		strcat(s,s2);
		strcpy(s1,"| cut -f1 -d ' ' > file.txt"); // Remove the filename and gives the word count alone
		strcat(s,s1);
		system(s);
		
		file>>bt[i];
		file.close();
		
		//st_ctime: time of last file status change
		struct stat t_stat;
		stat(s2,&t_stat);
		struct tm *timeinfo = localtime(&t_stat.st_ctime);
		
		int hour,minutes,seconds;
		
		hour=timeinfo->tm_hour;
		minutes=timeinfo->tm_min;
		seconds=timeinfo->tm_sec;
		//cout<<hour<<" "<<minutes<<" "<<seconds<<endl;
		at[i]=(hour*60*60)+(minutes*60)+seconds;
		
	
	}

}
