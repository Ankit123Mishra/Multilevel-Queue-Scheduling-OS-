//3324325
#include<iostream>
using namespace std;
#include<queue>

//global variables
int n;
int a[100][7];
int tq=4;
int timeRoundRobin;
int timePriority;
int time=0;
int start=0;

//queues
queue<int*> q1;
queue<int*> q2;
queue<int*> q3;
queue<int*> qn;

//functions
int roundrobin();
int priority();
void assignQueues(int end);
void display(queue<int*> q);
void assignQueuesInitial();
//void callingRR();
//void callingPriority();
void getdata();
void ordering(queue<int*> q);

main()
{
	int w;
	getdata();
    roundrobin();
}

void display(queue<int*> q)
{
	queue<int*> g=q;
	string dem="";
	while(!g.empty())
	{
		cout<<dem<<"P"<<g.front()[0];
		dem="-->";
		g.pop();
	}
	cout<<"\n";
}

void getdata()
{
	cout<<"How many processes do you want?";
	cin>>n;
	//take input from the user of all the processes
	for(int i=0;i<n;i++)
	{
		cout<<"Process "<<i+1<<":";
		a[i][0]=i+1;
		cout<<"\n Priority(0-9) : ";
		cin>>a[i][1];
		cout<<"\n Arrival Time : ";
		cin>>a[i][2];
		cout<<"\n Burst Time : ";
		cin>>a[i][3];
		//remaining time
		a[i][4]=a[i][3];
		//completion time
		a[i][5]=0;
		//turnaround time
		a[i][6]=0;
		//waiting time
		a[i][7]=0;
		qn.push(a[i]);
	}
}

int checkduplicates(queue<int*> q, int p)
{
	queue<int*> g=q;
	while(!g.empty())
	{
		if(g.front()[0]==p)
		{
			return 1;
			break;
		}
		g.pop();
	}
	return 0;
}
void assignQueues(int end)
{
	queue<int*> q=qn;
	queue<int*> g;
	while(!q.empty())
	{
		int f=0;
		if(q.front()[2]<=end)
		{
			if(q.front()[1]>0 && q.front()[1]<=3)
			{
				int c=checkduplicates(q1,q.front()[0]);
				if(c==0)
				{
					q1.push(q.front());
				}
			}
			else if(q.front()[1]>3 && q.front()[1]<=6)
			{
				int c=checkduplicates(q2,q.front()[0]);
				if(c==0)
				{
					q2.push(q.front());
				}
			}
		   	f=1;
		   	qn.pop();
		}
		if(f==0)
		{
		   g.push(q.front());
		   qn.pop();	
		}
		q.pop();
	}
	qn=g;
}

void displayProcess(int* a)
{
	cout<<"P"<<a[0]<<"-->";
}
int roundrobin()
{
	assignQueues(time);
	if(!q1.empty())
	{
	timeRoundRobin=0;
	queue<int*> temp;
    while(!q1.empty())
    {
    	if(timeRoundRobin+q1.front()[4]<=10)
    	{
    	if(q1.front()[4]<=tq && q1.front()[4]>0)
    	{
    		time=time+q1.front()[4];
    		timeRoundRobin=timeRoundRobin+q1.front()[4];
    		assignQueues(time);
    		q1.front()[4]=0;
    		displayProcess(q1.front());
    		q1.pop();
		}
		else if(q1.front()[4]>tq)
		{
			time=time+tq;
			timeRoundRobin=timeRoundRobin+tq;
			assignQueues(time);
			q1.front()[4]=q1.front()[4]-tq;
			displayProcess(q1.front());
			temp.push(q1.front());
			q1.pop();
			q1.push(temp.front());
			temp.pop();
		}
	    }
	    else
		{
	    	int diff=10-timeRoundRobin;
	    	time=time+diff;
	    	assignQueues(time);
	    	timeRoundRobin=10;
	    	displayProcess(q1.front());
	    	q1.front()[4]=q1.front()[4]-diff;
	    	priority();
	    	return 1;
		}
	}
    }
    priority();
	return 0;
}

void ordering(queue<int*> q)
{
	int c[100][7];
	int b[100][7];
	queue<int*> g=q;
	int i=0;
	while(!g.empty())
	{
		for(int j=0;j<7;j++)
		{
			b[i][j]=g.front()[j];
		}
		i++;
		g.pop();
	}
	for(int i=0;i<q.size();i++)
	{
		for(int j=0;j<7;j++)
		{
		c[i][j]=b[i][j];
	    }
	}
	for(int k=0;k<i;k++)
	{
	    int min=c[0][1];
	    int p=0;
	for(int j=0;j<i;j++)
	{
		if(c[j][1]<min)
		{
			min=c[j][1];
			p=j;
		}
	}
	c[p][1]=10000;
	g.push(b[p]);
    }
	q2=g;
}
int priority()
{
	assignQueues(time);
	if(!q2.empty())
	{
	ordering(q2);
	timePriority=0;
    while(!q2.empty())
    {
    	if(timePriority+q2.front()[4]<=10)
    	{
    	time=time+q2.front()[4];
    	timePriority=timePriority+q2.front()[4];
    	q2.front()[4]=0;
    	displayProcess(q2.front());
    	q2.pop();
    	assignQueues(time);
    	ordering(q2);
        }
        else
        {
        	int diff=10-timePriority;
        	time=time+diff;
        	assignQueues(time);
	    	timePriority=10;
	    	displayProcess(q2.front());
	    	q2.front()[4]=q2.front()[4]-diff;
	    	roundrobin();
			return 1;
		}
	}
    }
    roundrobin();	
    return 0;
}
