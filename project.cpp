//github current commit
#include<iostream>
using namespace std;
#include<queue>

//global variables
int n;
int a[100][8];
int tq=4;
int timeRoundRobin;
int timePriority;
int timeFcfs;
int time=0;
int maxAT;

//queues
queue<int*> q1;
queue<int*> q2;
queue<int*> q3;
queue<int*> qn;

//functions
int roundrobin();
int priority();
int fcfs();
void assignQueues(int end);
void display(queue<int*> q);
void getdata();
void ordering(queue<int*> q);
void orderingfcfs(queue<int*> q);
void displayProcess(int* r);
int find(int w);
int checkduplicates(queue<int*> q, int p);

main()
{
	getdata();
	cout<<"\nGantt Chart:\n";
    roundrobin();
    cout<<"\n\nThe final CPU analysis:\n";
    cout<<"\nPNO\tPrority\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for(int i=0;i<n;i++)
    {
    	cout<<"P"<<a[i][0]<<"\t"<<a[i][1]<<"\t"<<a[i][2]<<"\t\t"<<a[i][3]<<"\t\t"<<a[i][5]<<"\t\t"<<a[i][6]<<"\t\t"<<a[i][7];
    	cout<<"\n";
	}
}

void display(queue<int*> q)
{
	queue<int*> g=q;
	string dem="";
	if(q.empty())
	{
		cout<<"\nqn-->Empty queue\n";
	}
	else{
	while(!g.empty())
	{
		cout<<dem<<"P"<<g.front()[0];
		dem="-->";
		g.pop();
	}
	cout<<"\n";
    }
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
	int min=a[0][2];
	for(int i=0;i<n;i++)
	{
		if(a[i][2]<min)
		{
			min=a[i][2];
		}
	}
	time=time+min;
	int max=a[0][2];
	for(int i=0;i<n;i++)
	{
		if(a[i][2]>max)
		{
			max=a[i][2];
		}
	}
	maxAT=max;	
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
	if(!qn.empty())
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
			else
			{
				int c=checkduplicates(q3,q.front()[0]);
				if(c==0)
				{
					q3.push(q.front());
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
}

int find(int w)
{
	int k;
	for(int i=0;i<n;i++)
	{
		if(a[i][0]==w)
		{
			k=w;
			break;
		}
	}
	return k;
}
void displayProcess(int* r)
{
	int k=find(r[0]);
	a[k-1][5]=time;
	a[k-1][6]=a[k-1][5]-a[k-1][2];
	a[k-1][7]=a[k-1][6]-a[k-1][3];
	cout<<"P"<<r[0]<<"-->";
}
int roundrobin()
{
	assignQueues(time);
	if(!q1.empty()||!q2.empty()||!q3.empty())
	{
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
    		cout<<"("<<time<<")";
    		q1.pop();
    		if(timeRoundRobin==10)
    		{
    			priority();
    			return 1;
			}
		}
		else if(q1.front()[4]>tq)
		{
			time=time+tq;
			timeRoundRobin=timeRoundRobin+tq;
			assignQueues(time);
			q1.front()[4]=q1.front()[4]-tq;
			displayProcess(q1.front());
			cout<<"("<<time<<")";
			temp.push(q1.front());
			q1.pop();
			q1.push(temp.front());
			temp.pop();
			if(timeRoundRobin==10)
			{
				priority();
				return 1;
			}
		}
	    }
	    else
		{
	    	int diff=10-timeRoundRobin;
	    	time=time+diff;
	    	assignQueues(time);
	    	timeRoundRobin=10;
	    	displayProcess(q1.front());
	    	cout<<"("<<time<<")";
	    	q1.front()[4]=q1.front()[4]-diff;
	    	priority();
	    	return 1;
		}
	}
    }
    priority();
    }
    if(time<maxAT)
    {
    	time=maxAT;
    	roundrobin();
	}
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
    	cout<<"("<<time<<")";
    	q2.pop();
    	assignQueues(time);
    	ordering(q2);
    	if(timePriority==10)
    	{
    		fcfs();
    		return 1;
		}
        }
        else
        {
        	int diff=10-timePriority;
        	time=time+diff;
        	assignQueues(time);
	    	timePriority=10;
	    	displayProcess(q2.front());
	    	cout<<"("<<time<<")";
	    	q2.front()[4]=q2.front()[4]-diff;
	    	fcfs();
			return 1;
		}
	}
    }
    fcfs();	
    return 0;
}

void orderingfcfs(queue<int*> q)
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
	    int min=c[0][2];
	    int p=0;
	for(int j=0;j<i;j++)
	{
		if(c[j][2]<min)
		{
			min=c[j][2];
			p=j;
		}
	}
	c[p][2]=10000;
	g.push(b[p]);
    }
	q3=g;
}


int fcfs()
{
	assignQueues(time);
	if(!q3.empty())
	{
		orderingfcfs(q3);
		timeFcfs=0;
		while(!q3.empty())
		{
			if(timeFcfs+q3.front()[4]<=10)
			{
			time=time+q3.front()[4];
			timeFcfs=timeFcfs+q3.front()[4];
			q3.front()[4]=0;
			displayProcess(q3.front());
			cout<<"("<<time<<")";
			assignQueues(time);
			orderingfcfs(q3);
			q3.pop();
			if(timeFcfs==10)
			{
				roundrobin();
				return 1;
			}
		    }
		   else
		   {
			int diff=10-timeFcfs;
        	time=time+diff;
        	timeFcfs=10;
        	q3.front()[4]=q3.front()[4]-diff;
        	displayProcess(q3.front());
        	cout<<"("<<time<<")";
			roundrobin();
			return 1;
		    }   
	    }
    }
	roundrobin();
	return 0;
}
