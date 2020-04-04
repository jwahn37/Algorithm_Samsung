#include <iostream>
using namespace std;

#define MAX_N (10)
#define MAX_INF (99999999)

typedef struct{ int x; int y;}AXIS;

int T;
int N;
AXIS home, company;
AXIS customers[MAX_N];
int passed[MAX_N];
int min_dist;

int solve();
void init();
void dfs_path(AXIS loc, int n_path, int dist);
int distance(AXIS loc1, AXIS loc2);

int main()
{
	ios_base:: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N;
		cin>>company.x>>company.y>>home.x>>home.y;
		for(int i=0; i<N; i++)
			cin>>customers[i].x>>customers[i].y;
		cout<<"#"<<t<<" "<<solve()<<endl;
	}
}

int solve()
{
	init();
	dfs_path(company, 0, 0);
	return min_dist;
}

void init()
{
	for(int i=0; i<MAX_N; i++)
	{
		passed[i] = 0;
	}
	min_dist = MAX_INF;
}

void dfs_path(AXIS loc, int n_path, int dist)
{		
	if(dist >= min_dist)	return;
	if(n_path == N)
	{
		dist += distance(loc, home);
		if(dist < min_dist)	
		{
			min_dist = dist;
		//	return min_dist;
		}
		return;
	}
	else
	{
		for(int i=0; i<N; i++)
		{
			if (passed[i] == 0)
			{
				passed[i] = 1;
				//dist += distance(loc, customers[i]);
				dfs_path(customers[i], n_path+1, dist + distance(loc, customers[i]));
				passed[i] = 0;
			}
		}
		return;
	}
}

int distance(AXIS loc1, AXIS loc2)
{
	int dist;
	dist = (loc1.x >= loc2.x) ? (loc1.x - loc2.x) : (loc2.x - loc1.x);
	dist += (loc1.y >= loc2.y) ? (loc1.y - loc2.y) : (loc2.y - loc1.y);
	return dist;
}
