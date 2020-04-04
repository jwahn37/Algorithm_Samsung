#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct edge{
	int v1, v2;
	int w;
	
	/*
	   bool operator<(const struct edge e)const{
		return (w<e.w)? true:false;
	}
	bool operator>(const struct edge e)const{
		return (w>e.w)? true:false;
	}
	*/
}EDGE;

bool comp(EDGE e1, EDGE e2)
{
	return (e1.w > e2.w) ? true : false;
}
vector<EDGE> edges;

int main()
{
	for(int i=0; i<10; i++)
	{
		EDGE e;
		e.v1 = i;
		e.v2 = i+1;
		e.w = 10-i;
		edges.push_back(e);
	}
	sort(edges.begin(), edges.end(), comp);
	for(int i=0; i<10; i++)
	{
		cout<<edges[i].w<<" ";
	}
	cout<<endl;


}
