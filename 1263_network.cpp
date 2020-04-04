#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX_N (1000)
#define MAX_INF (987654321)

vector<unsigned int> adj[MAX_N+1];
unsigned int N;
unsigned int dist[MAX_N+1][MAX_N+1];
unsigned int cc[MAX_N+1];

void make_graph();
unsigned int solve();
void print_1();
void print_2();
void init_dist();

int main()
{
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		make_graph();
		cout<<"#"<<t<<" "<<solve()<<endl;
	}
}

void make_graph()
{
	cin>>N;
	for(int v1=1; v1<=N; v1++)
	{
		adj[v1].clear();
		for(int v2=1; v2<=N; v2++)
		{
			int p;
			cin>>p;
			if(p==1)	adj[v1].push_back(v2);
		}
	}
//	print_1();
}

unsigned int solve()
{
	//플로이드 와샬 알고리즘
	//초기화
	init_dist();
	//DP
	for(int k=1; k<=N; k++)
	{
		for(int v1=1; v1<=N; v1++)
		{
			if(k==v1)	continue;
		//	cout<<"k,v: "<<k<<" "<<v1<<": ";
			for(int v2=1; v2<=N; v2++)
			{
				if((v1==v2) || (k==v2))	continue;
				//dist[k%2][v1][v2] = min(dist[(k-1)%2][v1][v2], dist[(k-1)%2][v1][k] + dist[(k-1)%2][k][v2]);
				dist[v1][v2] = min(dist[v1][v2], dist[v1][k] + dist[k][v2]);
		//		cout<<dist[k%2][v1][v2]<<" ";
				
			}
		//	cout<<endl;
		}
	}
//	cout<<"min "<<min(1, 2)<<endl;

	int minv=MAX_INF;
	for(int v1=1; v1<=N; v1++)
	{
		for(int v2=1; v2<=N; v2++)
		{
			if(v1!=v2)	cc[v1] += dist[v1][v2];
		}
		if(minv > cc[v1])	minv = cc[v1];
	}
	//print_2();

	return minv;	
}



void init_dist()
{

//	for(int k=0; k<2; k++)
//	{
		for(int v1=1; v1<=N; v1++)
		{
			for(int v2=1; v2<=N; v2++)
			{
				dist[v1][v2] = MAX_INF;
			}
		}
//	}

	for(int v1=1; v1<=N; v1++)
	{
		for(int i=0; i<adj[v1].size(); i++)
		{	
			dist[v1][adj[v1][i]] = 1;
		}

	}

	for(int v=1; v<=N; v++)
		cc[v] = 0;

}

void print_1()
{
	for(int v1=1; v1<=N; v1++)
	{
		cout<<v1<<": ";
		for(int i=0; i<adj[v1].size(); i++)
		{
			cout<<adj[v1][i]<<" ";
		}
		cout<<endl;
	}
}

void print_2()
{
	for(int v=1; v<=N; v++)
		cout<<cc[v]<<" ";
	cout<<endl;
}

