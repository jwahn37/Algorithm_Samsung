#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef struct{
	unsigned long long x, y;
}AXIS;
typedef struct{
	//AXIS v;
	int v;
	unsigned long long w;
}G_NODE;
typedef struct pq_node{
	int v;
	unsigned long long w;
	bool operator<(const struct pq_node t)const{
		return (w<t.w)? true : false;
	}
	bool operator>(const struct pq_node t)const{
		return (w>t.w)? true : false;
	}
}PQ_NODE;

const int MAX_V = 1001;
const unsigned long long INF = 999999999987654321;
int N;
double E;

AXIS nodes[MAX_V];
vector<G_NODE> adj[MAX_V];
//priority_queue<PQ_NODE, vector<PQ_NODE>, greater< PQ_NODE > > pq;
int parent[MAX_V];
unsigned long long weight[MAX_V];
int visited[MAX_V];

//about combination
int cn;
int cr;
vector<int> cselected;

unsigned long long solve();
void init();
void make_graph();
void nCr(int idx, int r);
void insert_node(int v1, int v2);
unsigned long long MST_prim();

void print_graph();

int main()
{
	unsigned long long res;
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N;
		for(int i=0; i<N; i++)
			cin>>nodes[i].x;
		for(int i=0; i<N; i++)
			cin>>nodes[i].y;
		cin>>E;
		res=solve();
		cout<<"#"<<t<<" "<<res<<endl;	
	}
}

unsigned long long solve()
{
	unsigned long long res_long;
	double res;

	init();
	make_graph();
	res=MST_prim();
	res*=E;
	res_long = res;

	if(res - res_long >= 0.5)
		res_long++;
	//cout.precision(10);
	//cout<<res<<endl;
	
	return res_long;
}

void init()
{
	for(int i=0; i<N; i++)
	{
		adj[i].clear();
		parent[i] = i;
		weight[i] = INF;
		visited[i] = 0;
	}
//	pq.clear();
	cselected.clear();
}

void make_graph()
{
	//nodes에서 2개를 골라서 weight를 구하는 모든 경우의 수	
	//nCr(N, 2, 0, 0);
	cn = N;
	cr = 2;
	nCr(0, 0);
//	print_graph();
}

void nCr(int idx, int r)
{
	if(r>=cr){
		//두개의 정점을 이용하여 그래프 노드 삽입
	//	cout<<cselected[0]<<" "<<cselected[1]<<endl;
		insert_node(cselected[0], cselected[1]);	
	}
	else{
		for(int i=idx; i<cn; i++)
		{
			cselected.push_back(i);
			nCr(i+1, r+1);
			cselected.pop_back();
		}
	}
}

void insert_node(int v1, int v2)
{
	unsigned long long w;
	w = (nodes[v1].x-nodes[v2].x) * (nodes[v1].x - nodes[v2].x);
	w += (nodes[v1].y-nodes[v2].y) * (nodes[v1].y - nodes[v2].y);
//	w = sqrt(w);
//	w *= E;

	G_NODE n;
	n.v = v2;
	n.w = w;
	adj[v1].push_back(n);
	n.v = v1;
	adj[v2].push_back(n);

	return;
}

unsigned long long MST_prim()
{
	//int v = 0;//최초 정점
	priority_queue<PQ_NODE, vector<PQ_NODE>, greater< PQ_NODE > > pq;
	PQ_NODE pq_cur, pq_next;
	unsigned long long cost=0;
	pq_cur.v = 0;
	pq_cur.w = 0;
	pq.push(pq_cur);

	int iter = N;
	while(!pq.empty())
	//while(N--)
	{
	//	cout<<"PRIM while"<<endl;
		pq_cur = pq.top();
		pq.pop();
	
	//	if(pq_cur.w > weight[pq_cur.v])	continue;
		if(visited[pq_cur.v])
		{
			N++;
			continue;
		}
		visited[pq_cur.v] = 1;

		cost+=pq_cur.w;

		for(int i=0; i<adj[pq_cur.v].size(); i++)
		{
			int v_next = adj[pq_cur.v][i].v;
			unsigned long long w_next = adj[pq_cur.v][i].w;
		//	cout<<"PRIM "<<v_next<<" "<<w_next<<endl;
			if(weight[v_next] > w_next)
			{
				weight[v_next] = w_next;
				parent[v_next] = pq_cur.v;
				pq_next.v = v_next;
				pq_next.w = w_next;
				pq.push(pq_next);
			}
		}
	}
	return cost;
}

void print_graph()
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<adj[i].size(); j++)
		{
			cout<<adj[i][j].v<<", "<<adj[i][j].w<<" ";
		}
		cout<<endl;
	}
}
