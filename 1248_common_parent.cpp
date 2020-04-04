#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_V (10001)

void init();
void make_tree(int parent, int child);
void solve(int* com_parent, int* n_subtrees);
void insert_level();
int find_com_parent();
int find_n_subtrees(int node);
void print_all();

int V, E;
int v1, v2;
int t_level[MAX_V];
int t_parent[MAX_V];
vector<int> tree[MAX_V];
//int com_parent, n_subtrees;

int main()
{
	int T;
	int p, c;
	int com_parent, n_subtrees;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>T;
	for(int t=1; t<=T; t++)
	{
		init();
		cin>>V>>E>>v1>>v2;
		for(int i=1; i<=E; i++)
		{
			cin>>p>>c;
			make_tree(p, c);
		}
		solve(&com_parent, &n_subtrees);
		cout<<"#"<<t<<" "<<com_parent<<" "<<n_subtrees<<endl;
	}
	//print_all();
}	

void init()
{
	for(int i=1; i<MAX_V; i++)
	{
		tree[i].clear();
		t_parent[i]=0;
		t_level[i]=0;
	}
//	com_parent = 0;
//	n_subtrees = 0;
}

void make_tree(int parent, int child)
{
	tree[parent].push_back(child);
	t_parent[child] = parent;
}

void solve(int* com_parent, int* n_subtrees)
{

	insert_level();
	*com_parent = find_com_parent();
	*n_subtrees = find_n_subtrees(*com_parent);
}

void insert_level()
{
	queue<int> q;
	int cur_node;

	t_level[1] = 1;	//루트 노드는 level 1
	q.push(1);
	while(!q.empty())
	{
		cur_node = q.front();
		q.pop();
		for(int i=0; i<tree[cur_node].size(); i++)
		{
			t_level[tree[cur_node][i]] = t_level[cur_node]+1;
			q.push(tree[cur_node][i]);
		}
	}
}

int find_com_parent()
{
	int p1, p2;

	p1 = v1;
	p2 = v2;

	while(1)
	{
		if(p1 == p2)	return p1;

		if(t_level[p1] > t_level[p2])
			p1 = t_parent[p1];
		else
			p2 = t_parent[p2];
	}
}

int find_n_subtrees(int node)
{
	int cur_node;
	int cnt=0;
	queue<int> q;

	q.push(node);
	while(!q.empty())
	{
		cur_node = q.front();
		q.pop();
		cnt++;

		for(int i=0; i<tree[cur_node].size(); i++)
		{
			q.push(tree[cur_node][i]);
		}
	}
	return cnt;
}

void print_all()
{
	cout<<"parent,level: "<<endl;
	for(int v=1; v<=V; v++)
		cout<<v<<" "<<t_parent[v]<<" "<<t_level[v]<<endl;
}
