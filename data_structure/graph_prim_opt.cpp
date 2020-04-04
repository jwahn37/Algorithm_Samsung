#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//삼성 소프트웨어 알고리즘 강의 수도코드 구현
//priority queue를 이용한 성능향상!

/*
Tree -> weight와 parent 저장 (weight는 노드와 parent 사이의 가중치)
Priority queue -> weight, vertex 저장
graph node -> target의 weight, vertex 저장
   */
typedef struct{ int weight, parent; }T_NODE;
typedef struct pq_node{ 
	int weight, vertex; 
	bool operator<(const struct pq_node to)const{
		return (weight < to.weight)? true : false;
	}
}PQ_NODE;
typedef struct g_node{ int weight, vertex; }G_NODE;

const int MAX_V = 100;
const int INF = 987654321;
vector<G_NODE> adj[MAX_V]; //graph
priority_queue <PQ_NODE> q;
T_NODE tree[MAX_V];

/*
   자료구조 설정부터 굉장히 헷갈린다.
   node를 용도별로 재정의하는게 좋은 단순화일 수 있다.
   */

void MST_PRIM()
{
	//init spanning tree structure
	for(int i=0; i<MAX_V; i++)
	{
		tree[i].weight = INF;
		tree[i].parent = 0;
	}
	tree[0].weight = 0;
	
	//priority queue 초기화 (모든 노드 삽입)
	for(int i=0; i<MAX_V; i++)
	{
		PQ_NODE cur_pqnode;
		cur_pqnode.weight = tree[i].weight;
		cur_pqnode.vertex = i;
		q.push(cur_pqnode);
	}

	//V번 반복 순회하면서 spanning tree만들기
	while(!q.empty())
	{
		PQ_NODE cur_pqnode= q.top();
		int u = cur_pqnode.vertex;
		q.pop();
	
		//인접 노드 순회하면서 update하기
		for(int i=0; i<adj[u].size(); i++)
		{
			PQ_NODE next_pqnode;
			int v, w;
			v = adj[u][i].vertex;
			w = adj[u][i].weight;
		
			if(w < tree[v].weight)
			{
				tree[v].parent = u;
				tree[v].weight = w;
				//priority queue에 다시 삽입
				//중복은 고민 안해도 된다. 어차피 나중에 비교해서 날라감.
				next_pqnode.vertex = v;
				next_pqnode.weight = w;
				q.push(next_pqnode);
			}
		}		
	}	
}

int main()
{
	return 0;
}	
