#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef sturct g_node{
	int v, w;
}G_NODE;
typedef struct pq_node{
	int v, w;
	bool operator<(const struct pq_node target)const{
		return (w<target.w)? true : false;
	}
}PQ_NODE;

const int MAX_V = 10;
const int INF = 987654321;
vector<G_NODE> adj[MAX_V];
priority_queue<PQ_NODE, greater<PQ_NODE> >pq; 

int d[MAX_V];
int p[MAX_V];

void dijkstra(int v)
{
	for(int i=0; i<MAX_V; i++)
	{
		d[i] = INF;
		p[i] = 0;
	}
	d[v] = 0;
	p[v] = v;

	PQ_NODE cur_node, next_node;
	cur_node.v = v;
	cur_node.w = 0;
	pq.push(cur_node);

	while(!pq.empty())
	{
		cur_node = pq.top();
		pq.pop();
	
		if(d[cur_node.v] < cur_node.w)	continue;
		
		for(int i=0; i<adj[cur_node.v].size(); i++)
		{
			int tv = adj[cur_node.v][i].v;
			int tw = adj[cur_node.v][i].w;

			if(d[tv] > d[cur_node.v] + tw)
			{
				d[tv] = d[cur_node.v] + tw;
				p[tv] = cur_node.v;
				
				next_node.v = tv;
				next_node.w = d[tv];
				pq.push(next_node);
			}
		}
	}

}
