#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef struct edge{
	int v1, v2;
	int w;
}EDGE;
bool comp(EDGE e1, EDGE e2)
{
	return (e1.w < e2.w)? true : false; //오름차순
}

typedef struct g_node{
	int v;
	int w;
}G_NODE;

const int MAX_V = 10;	//vertex 갯수
vector<EDGE> edges;
vector<G_NODE> adj[MAX_V];
int parent[MAX_V];	//disjoint set

//disjoint set은 여기서 구현을 생략함 함수 있다고 가정
void MST_kruscal()
{
	vector<EDGE> mst;
	for(int i=0; i<MAX_V; i++)
		make_set(i);
	//edge를 오름차순으로 정렬한다.
	sort(edges.begin(), edges.end(), comp);
	
	for(int i=0, int j=0; i<MAX_V; i++)
	{
		EDGE e = edges[++j];	
		if(find_set(e.v1) != find_set(e.v2))	//cycle 확인
		{
			mst.push_back(e);
			union_set(e.v1, e.v2);
		}
	}
}
