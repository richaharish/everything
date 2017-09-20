#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
using namespace std;
int count=0;
void randomsort(int a[], int n)
{
	int t,j;
	for(int i=n-1;i>0;i--)
	{
		j=rand()%i; //picking random index
		t=a[i];
		a[i]=a[j];
		a[j]=t;
	}
}
void counte(int a[],int n)
{
	int flag=0;
	for(int k=0;k<n;k++)
        	if(a[k]>a[k+1])
        	{
        		flag=1;
        		break;	
			}
    if(flag==0)
        count++;
}
int main()
{
	int a[50],n,k;
	cout<<"Enter the number of elements: ";
	cin>>n;
	srand(time(NULL));
	 for(int i=0;i<10;i++)
	 {
	 	cout<<"\n";
        for(int j=0;j<n; j++)
        	a[j]=rand()%10;
        randomsort(a,n);
        for(k=0;k<n;k++)
        cout<<a[k]<<" ";
        cout<<endl;
        counte(a,n);
	 }
	cout<<"The number of sorted arrays : "<< count;
	return 0;
}
