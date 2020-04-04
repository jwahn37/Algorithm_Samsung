#include<iostream>
#include<vector>


//알고리즘 문제 해결 전략 프림 알고리즘
//O(|V|^2)
//우선순위큐를 이용한다면(삼성 소프트웨어 알고리즘 강의)
//O(|V|log(|V|))?
//정확한 코드는 1251번 답 확인
const int MAX_V = 100;
const int INF = 987654321;
int V;
vector<pair<int, int> >adj[MAX_V];	//target vertex, edge weight

int prim(vector<pair<int, int> >& selected)
{
	selected.clear();
	vector<bool> added(V, false); 
	vector<int> minWeight(V, INF), parent(V, -1);

	int ret = 0;

	minWeight[0] = parent[0] = 0;
	for(int iter=0; iter<V; ++iter)
	{
		int u = -1;
		//다음에 조사할 최소 weight를 가지는 정점 찾기 O(|V|)
		for(int v=0; v<V; ++v)
		{
			if(!added[v] && (u==-1 || minWeight[u] > minWeight[v]))
				u=v;
		}
		if(parent[u] != u)
			selected.push_back(make_pair(parent[u], u));
		ret += minWeight[u];
		added[u] = true;
		//u에 인접한 간선 업데이트
		for(int i=0; i<adj[u].size(); ++i)
		{
			int v = adj[u][i].first, weight = adj[u][i].second;
			if(!added[v] && minWeight[v] > weight)
			{
				parent[v] = u;
				minWeight[v] = weight;
			}
	}
}
